#include <iostream>
#include "vector"

using namespace std;

vector<double> X;
vector<double> Y;
int N;
int n;
double *A;
double *p;
double *x;
double *m;
double *b;

// ********************************* Initialization and Write Vector/Matrix *********************************
/**
 * Allocates a n sized vector and initializes all entries to 0
 * @param n
 * @return Pointer of double array.
 */
double *allocate_vector (uint64_t size)
{
    double *v;
    v = (double *) calloc(size, sizeof(double)); //Allocation array with calloc.
    return v;
}

//----------------------------------------------------------------------------------------------------

/**
 * Writes a matrix to a stream. For example, writing a matrix to standard output is
 * writeMatrix(stdout, A, n, m);
 * A sream can also be a file.
*/
void write_matrix (FILE *stream, double *w, uint64_t n_, uint64_t m_)
{
    fprintf(stream, "%d %d \n", (int)n_, (int)m_); //Initalization format.
    int i, j;
    for(i = 0; i < n_; ++i)
    {
        for(j = 0; j < m_; ++j)
        {
            fprintf(stream, "%f \t", w[i * m_ + j]); //
        }
        fprintf(stream, "\n");
    }
}

// ****************************** Create and initialize vector and matrix for spline ******************************
/**
 * Initialization matrix of tridiagional system. Am = b.
 */
void create_A ()
{
    for (int i = 1 ; i < N - 1; ++i) {
        A[(i - 1) * (N - 2) + (i - 1)] = (X[i + 1] - X[i - 1]) / 3;
        A[(i - 1) * (N - 2) + i] = (X[i + 1] - X[i]) / 6;
        A[i * (N - 2) + (i - 1)] = (X[i + 1] - X[i]) / 6;
    }

    A[(N - 2) * (N - 2) + (N - 2)] = (X[N - 1] - X[N - 2]) / 3;
}

//----------------------------------------------------------------------------------------------------

/**
 * Initialization vector of resolution system. Am = b.
 */
void create_b () {
    for (int i = 1 ; i < N - 1 ; ++i) {
        b[i - 1] = ((Y[i + 1] - Y[i]) / (X[i + 1] - X[i])) - ((Y[i] - Y[i - 1]) / (X[i] - X[i - 1]));
    }
}

//----------------------------------------------------------------------------------------------------

/**
 * Initialization vector of derivative seconde. Am = b.
 */
void create_m () {
    m[0] = 0;
    m[N -1] = 0;
    for (int i = 1 ; i < N ; ++i) {
        m[i] = x[i - 1];
    }
}

//----------------------------------------------------------------------------------------------------

/**
 * Iniitialization matrix of polynomial a0 + a1x + a2x² + a3x³
 */
void create_p () {
    for (int i = 1 ; i < N ; ++i) {

        p[(i - 1) * 4 + 0] = Y[i - 1];
        p[(i - 1) * 4 + 1] = ((Y[i] - Y[i - 1]) / ((X[i] - X[i - 1])) - ((X[i] - X[i - 1]) / 6) * (m[i] + 2 * m[i - 1]));
        p[(i - 1) * 4 + 2] = (m[i - 1] / 2);
        p[(i - 1) * 4 + 3] = (m[i] - m[i - 1]) / (6 * (X[i] - X[i - 1]));

    }
}

// ************************************ System Gauss ************************************

/**
 * If error, Center ligne switch.
 * @param indexLigneOrigine
 * @param indexLigneFinal
 */
void switch_line (int indexLigneOrigine, int indexLigneFinal) {
    double* Amemories = allocate_vector(n);
    for (int j = 0 ; j < n ; ++j) {
        Amemories[j] = A[indexLigneFinal * n + j];
        A[indexLigneFinal * n + j] = A[indexLigneOrigine * n + j];
        A[indexLigneOrigine * n + j] = Amemories[j];
    }
}

//----------------------------------------------------------------------------------------------------

/**
 * Verification of diganial line is not zero.
 * @param error
 */
void switch_and_verification_zero_column (bool & error) {
    bool errorV = false;
    for ( int i = 0 ; i < n ; ++i ) {
        if (A[i * n + i] == 0) {
            for ( int j = i ; j < n ; ++j ) {
                if (A[j * n + i] != 0) {
                    switch_line(i, j);
                    error = errorV;
                }
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------

/**
 * Performs Gauss elimination for given a matrix A (size n x n) and a vector b (size n).
    Modifies directly matrix A and vector b.
    In the end of the procedure, A is upper truangular and b is modified accordingly.
    Returns a boolean variable:
        *  true in case of success and
        *  false in case of failure, for example matrix is impossible to triangularize.
 * @return
 */
bool triangularize (){
    double addition;
    bool error = true;
    for ( int i = 0 ; i < n - 1 ; ++i ) {
        if ( A[i * n + i] == 0 ) {
            switch_and_verification_zero_column(error);
        }
        for ( int k = i ; k < n - 1 ; ++k ) {
            addition = A[(k + 1) * n + i] / A[i * n + i];
            for ( int j = i ; j < n ; ++j ) {
                A[(k + 1) * n + j] = A[(k + 1) * n + j] - addition * A[i * n + j];
            }
            b[k + 1] = b[k + 1] - addition * b[i];
        }
    }
    return error;
}

//----------------------------------------------------------------------------------------------------

/**
 *Solves a system of linear equations Ax=b for a double-precision matrix A (size n x n).
 *Uses iterative ascension algorithm.
 *After the procedure, x contains the solution of Ax=b.
*/
void solve_triangular_system_UP (){
    if(triangularize()){
        for(int i = n - 1 ; i >= 0 ; i--){
            b[i] = b[i]/A[i * n + i];
            A[i * n + i] = 1;
            for(int j = i - 1 ; j >= 0 ; j--){
                b[j] = b[j]-b[i]*A[j * n + i];
                A[j * n + i] = 0;
            }
        }
        for(int i = 0 ; i < n ; ++i){
            x[i] = b[i];
        }
    }
}

//----------------------------------------------------------------------------------------------------

/**
 * Solves a system of linear equations Ax=b, given a matrix A (size n x n) and vector b(size n).
 * Uses Gauss elimination algorithm based on truangularization and the ascension solving.
        Returns a boolean variable:
        *  true in case of success and
        *  false in case of failure, for example matrix is of rank <n .
 * @return error
 */
bool solve_system_gauss (){

    bool error;

    error = triangularize();
    solve_triangular_system_UP();

    return error;
}

// ******************************************** Calcul polynomial ********************************************

/**
 * Search the index between two number of table number X.
 * @param absiss value of absiss for the function.
 * @return the corresponding index (-1 if impossible).
 */
int search_index (double absiss) {
    int index = -1;

    for (int i = 1 ; i < N ; ++i) {
        if ( absiss >= X[i - 1] && absiss < X[i]) {
            return i - 1;
        }
    }
    return index;
}

//----------------------------------------------------------------------------------------------------

/**
 * Calcul with the good polynom a number.
 * @param x
 * @return Result of calcul.
 */
double polynom (double absiss) {
    int index;
    if ((index = search_index(absiss)) != -1) {
        return p[index * 4 + 0] + (absiss - X[index]) * (p[index * 4 + 1] + (absiss - X[index]) * (p[index * 4 + 2] + p[index * 4 + 3] * (absiss - X[index])));
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------

/**
 * Calcul with the good polynom double array.
 * @param u
 */
void polynom (const vector<double>& u) {

    if (!u.empty()) {
        cout << "\n" << endl;
        cout << "Solution Pi(u) : " << endl;
        for (double i : u) {
            cout << polynom(i) << endl;
        }
        cout << "\n" << endl;
    }
}

/**
 * Verification and initialization var.
 * @param XX
 * @param YY
 * @return error in int (-1, -2 or 0).
 */
int initialization (vector<double> XX, const vector<double>& YY) {
    if ((N = XX.size()) == YY.size() && N > 2) {
        for (int i = 0 ; i < N - 1 ; ++i) {
            if (XX[i + 1] <= XX[i]) {
                cout << "Abscissa error : Is not strictly increasing." << endl;
                return -1;
            }
        }
        X = XX;
        Y = YY;

        n = N - 2;
        A = (double *) calloc((N - 2) * (N -2), sizeof(double));
        p = (double *) calloc((N - 1) * 4, sizeof(double));
        x = (double *) calloc(N - 2, sizeof(double));
        m = (double *) calloc(N, sizeof(double));
        b = (double *) calloc(N - 2, sizeof(double));

        return 0;
    } else {
        cout << "Size error : datas must be superior to two." << endl;
        return -2;
    }
}

/**
 * Start initialization and draw result.
 */
void start () {
    create_A();
    create_b();

    cout << "\n***************************************************** Ax = b *****************************************************" << endl;
    cout << "\nMatrix A :" << endl;
    write_matrix(stdout, A, N - 2, N - 2);

    cout << "\nMatrix b :" << endl;
    write_matrix(stdout, b, N - 2, 1);

    if (!solve_system_gauss()) {
        cout << "singular problem : Impossible to solve system." << endl;
        exit(0);
    }

    cout << "\nSolution matrix x :" << endl;
    write_matrix(stdout, x, n, 1);

    cout << "\nMatrix m :" << endl;
    create_m();
    write_matrix(stdout, m, N, 1);

    cout << "\nMatrix p polynomial:" << endl;
    create_p();
    write_matrix(stdout, p, N - 1, 4);
}

// ******************************************** MAIN ********************************************

int main () {

    // -------------------------------------- IN --------------------------------------
    vector<double> XX = {-3.8, -3, -1.9, -0.3, 0.9, 2.1, 3.1, 4.2, 5.4};
    vector<double> YY = {0.19, 0.46, 0.48, -0.19, 1.3, 0.19, 0.29, 0.4, -0.57};

    // -------------------------------- Initialization --------------------------------
    if (initialization(XX, YY) != 0) {
        exit(0);
    }
    start();

    // ------------------------------------- Test -------------------------------------
    vector<double> u = {-3.4, -3.38, -3.2, -1.98, -1.44, 1.42, 2.19, 5.34};
    polynom(u);

}
