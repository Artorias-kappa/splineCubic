

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
 * @role : Allocates a n sized vector and initializes all entries to 0.
 * @param : size
 * @return : Pointer of double array.
 */
double *allocate_vector (uint64_t size)
{
    double *v;
    v = (double *) calloc(size, sizeof(double)); //Allocation array with calloc.
    return v;
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Writes a matrix to a stream. For example, writing a matrix to standard output is
 * writeMatrix(stdout, A, n, m);
 * A sream can also be a file.
*/
void write_matrix (FILE *stream, double *w, uint64_t n_, uint64_t m_)
{
    int i, j;
    for(i = 0; i < n_; ++i)
    {
        for(j = 0; j < m_; ++j)
        {
            fprintf(stream, "%f \t", w[i * m_ + j]); //Display matrix.
        }
        fprintf(stream, "\n");
    }
}

// ****************************** Create and initialize vector and matrix for spline ******************************
/**
 * @role : Initialization matrix of tridiagional system. Ax = b.
 */
void create_A ()
{
    for (int i = 1 ; i < N - 1; ++i) {
        A[(i - 1) * (N - 2) + (i - 1)] = (X[i + 1] - X[i - 1]) / 3; //Calcul of diagonal center : (X_n - X_n-2) / 3.
        A[(i - 1) * (N - 2) + i] = (X[i + 1] - X[i]) / 6; //Calcul of diaganal down : (X_n-2 - Xn-1) / 6.
        A[i * (N - 2) + (i - 1)] = (X[i + 1] - X[i]) / 6; //Calcul of diaganal up : (X_n-2 - Xn-1) / 6.
    }

    A[(N - 2) * (N - 2) + (N - 2)] = (X[N - 1] - X[N - 2]) / 3; //Calcul of position n*n. This calculation is for the last number of matrix.
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Initialization vector of resolution system. Ax = b.
 */
void create_b () {
    for (int i = 1 ; i < N - 1 ; ++i) {
        b[i - 1] = ((Y[i + 1] - Y[i]) / (X[i + 1] - X[i])) - ((Y[i] - Y[i - 1]) / (X[i] - X[i - 1])); // In matematics, the calculation is : [(Y_n - Y_n-1) / (X_n - X_n-1)] - [(Y_n-1 - Y_n-2) / (X_n-1 - X_n-2)]
    }
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Construction matrix m, with 0 to position m_0 and m_n.
 */
void create_m () {
    m[0] = 0; //Inite m_0.
    m[N - 1] = 0; //Inite m_n
    for (int i = 1 ; i < N ; ++i) {
        m[i] = x[i - 1]; //Copy X_1 to X_n-1 in m.
    }
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Iniitialization matrix of polynomial a0 + a1x + a2x² + a3x³
 */
void create_p () {
    for (int i = 1 ; i < N ; ++i) {

        p[(i - 1) * 4 + 0] = Y[i - 1]; //Coefficient a0 = Y_n-1.
        p[(i - 1) * 4 + 1] = ((Y[i] - Y[i - 1]) / ((X[i] - X[i - 1])) - ((X[i] - X[i - 1]) / 6) * (m[i] + 2 * m[i - 1])); //Coefficient a1 = ( [(Y_n - Y_n-1) / (X_n - X_n-1)] - [(X_n - X_n-1) / 6] ) * (m_n + 2*m_n-1).
        p[(i - 1) * 4 + 2] = (m[i - 1] / 2); //Coefficient a2 = m_n-1 / 2.
        p[(i - 1) * 4 + 3] = (m[i] - m[i - 1]) / (6 * (X[i] - X[i - 1])); //Coefficient a3 = [(m_n - m_n-1) / (6 * (X_n - X_n-1))].

    }
}

// ************************************ System Gauss ************************************
/**
 * @role : If error, this procedure switch line in matrix.
 * @param indexOriginalLine represent the original line.
 * @param indexFinalLine represent the final line choice by the procedure.
 */
void switch_line (int indexOriginalLine, int indexFinalLine) {
    double* A_memories = allocate_vector(n);
    for (int j = 0 ; j < n ; ++j) {
        A_memories[j] = A[indexFinalLine * n + j];
        A[indexFinalLine * n + j] = A[indexOriginalLine * n + j];
        A[indexOriginalLine * n + j] = A_memories[j];
    }
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : This function finds if in the matrix there are an entire line of zeros.
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
 * Modifies directly matrix A and vector b.
 * In the end of the function, A is upper truangular and b is modified accordingly.
 *
 * @return boolean :
 *     - true in case of success.
 *     -  false in case of failure, for example matrix is impossible to triangularize.
 */
bool triangularize (){
    double addition;
    bool error = true;

    for ( int i = 0 ; i < n - 1 ; ++i ) {
        if ( A[i * n + i] == 0 ) {
            switch_and_verification_zero_column(error); //COMMENTAIRE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        }
        for ( int k = i ; k < n - 1 ; ++k ) {
            addition = A[(k + 1) * n + i] / A[i * n + i]; //Search coefficient depending pivot.
            for ( int j = i ; j < n ; ++j ) {
                A[(k + 1) * n + j] = A[(k + 1) * n + j] - addition * A[i * n + j]; //Multiply variable in matrix by coefficient "addition".
            }
            b[k + 1] = b[k + 1] - addition * b[i]; //Solve vector b by coefficient "addition".
        }
    }
    return error;
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Solves a system of linear equations Ax=b for a double-precision matrix A (size n x n).
 * Uses iterative ascension algorithm.
 * After the procedure, x contains the solution of Ax=b.
*/
void solve_triangular_system_UP (){

    if(triangularize()){

        for(int i = n - 1 ; i >= 0 ; i--){
            b[i] = b[i]/A[i * n + i];
            A[i * n + i] = 1;

            for(int j = i - 1 ; j >= 0 ; j--){
                b[j] = b[j]-b[i]*A[j * n + i];
                A[j * n + i] = 0; //Finds to make all the coefficient in column to zero.
            }
        }
        for(int i = 0 ; i < n ; ++i){
            x[i] = b[i]; //Solves equation at vector x such that Ax = b with
        }
    }
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Solves a system of linear equations Ax=b, given a matrix A (size n x n) and vector b(size n).
 * Uses Gauss elimination algorithm based on truangularization and the ascension solving.
 *
 * @return error :
 *      -  true in case of success and
 *      -  false in case of failure, for example matrix is of rank < n .
 */
bool solve_system_gauss (){

    bool error;

    error = triangularize(); //Triangulize the matrix, if the function failed, return "false".
    solve_triangular_system_UP();

    return error;
}

// ******************************************** Calcul polynomial ********************************************
/**
 * @role : Search the index between two number of table number X.
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
 * @role : Calcul with the good polynom a number.
 * @param absiss
 * @return Result of calcul.
 */
double polynom (double absiss) {
    int index;
    if ((index = search_index(absiss)) != -1) { //COMMENTAIRE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        return p[index * 4 + 0] + (absiss - X[index]) * (p[index * 4 + 1] + (absiss - X[index]) * (p[index * 4 + 2] +
                                                                                                   p[index * 4 + 3] *
                                                                                                   (absiss -
                                                                                                    X[index]))); //Calcul polynom_i = a0_1 + a1_i * x + a2_i * x² + a3_i * x³.    }
    }
    return -1;
}

//----------------------------------------------------------------------------------------------------
/**
 * @role : Calcul with the good polynom double array.
 * @param u
 */
void polynomial (const vector<double>& u) {

    if (!u.empty()) {
        cout << "\n" << endl;
        cout << "Solution Pi(u) :\n" << endl;
        for (double i : u) {
            cout << polynom(i) << endl; //Calcul a0_j + a1_j * u_i + a2_j * u_i² + a3_j * u_i³.
        }
        cout << "\n" << endl;
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @role : Verification and initialization var.
 * @param XX
 * @param YY
 * @return error in int (-1, -2 or 0).
 */
int initialization (vector<double> XX, const vector<double>& YY) {

    if ((N = XX.size()) == YY.size() && N > 2) {

        for (int i = 0 ; i < N - 1 ; ++i) {

            if (XX[i + 1] <= XX[i]) { // Test if entry in XX is strictly increasing.
                cout << "Abscissa error : Is not strictly increasing." << endl;
                return -1;
            }
        }

        //Initalization X and Y.
        X = XX;
        Y = YY;

        //Dimension matrix and array for resolution System gauss : Ax = b.
        n = N - 2;

        //Allocation array : x, m, b.
        //Allocation matrix : A, p.
        A = (double *) calloc(n * n, sizeof(double));
        p = (double *) calloc((N - 1) * 4, sizeof(double));
        x = (double *) calloc(n, sizeof(double));
        m = (double *) calloc(N, sizeof(double));
        b = (double *) calloc(n, sizeof(double));

        return 0;
    } else {
        cout << "Size error : datas must be superior to two." << endl;
        return -2;
    }
}

//---------------------------------------------------------------------------------------------------------------------
/**
 * @role : Start initialization and draw result.
 */
void start () {
    create_A();
    create_b();

    cout << "\n***************************************************** Ax = b *****************************************************" << endl;
    cout << "\nMatrix A :\n" << endl;
    write_matrix(stdout, A, n, n);

    cout << "\nMatrix b :\n" << endl;
    write_matrix(stdout, b, n, 1);

    if (!solve_system_gauss()) {
        cout << "singular problem : Impossible to solve system." << endl;
        exit(0);
    }

    cout << "\nSolution matrix x :\n" << endl;
    write_matrix(stdout, x, n, 1);

    cout << "\nMatrix m :\n" << endl;
    create_m();
    write_matrix(stdout, m, N, 1);

    cout << "\nMatrix p polynomial:\n" << endl;
    create_p();
    write_matrix(stdout, p, N - 1, 4);
}

// ******************************************** MAIN ********************************************

int main () {

    // -------------------------------------- IN --------------------------------------
    //An example takes in web-site of M BORER.
    vector<double> XX = {-3.8, -3, -1.9, -0.3, 0.9, 2.1, 3.1, 4.2, 5.4};
    vector<double> YY = {0.19, 0.46, 0.48, -0.19, 1.3, 0.19, 0.29, 0.4, -0.57};

    // -------------------------------- Initialization --------------------------------
    if (initialization(XX, YY) != 0) {
        exit(0);
    }
    start();

    // ------------------------------------- Test -------------------------------------
    vector<double> u = {-3.4, -3.38, -3.2, -1.98, -1.44, 1.42, 2.19, 5.34};
    polynomial(u);

}
