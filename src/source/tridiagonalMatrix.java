package source;

import java.util.ArrayList;

public class tridiagonalMatrix {
	private int lenght;
	
	private double matrix[];
	
	
	public tridiagonalMatrix(int lenght, double matrix[]) {
		
		this.lenght = lenght;
		this.matrix = matrix;
		
	}
	
	
	/**
	 * @role : solve the system 
	 * @param b :
	 * @return :
	 */
	public vector solveSystemLU(vector b) {
		vector x = null,y = null;
		tridiagonalMatrix A = copy();
		
		decompositionLU(A);
		solveTriangularSystemDown(x,A,b);
		solveTriangularSystemUP(x,A,y);
		
		return x;
	}
	
	private void solveTriangularSystemUP(vector x, tridiagonalMatrix A, vector y) {
		double value;
	    // we start with the last pivot (A[(n-1) * n + (n-1)]) and go up...
	    for(int i = A.lenght - 1 ; i >= 0 ; i--) {
	        y.tabElement.set(i, x.tabElement.get(i) / A.matrix[i * A.lenght + i]); // Look for the result of the only variable in the last row of A, such that t = ...

	        for (int j = i - 1; j >= 0; j--) {
	            value = x.tabElement.get(i) * A.matrix[j * A.lenght + i]; // ... then we replace (here t) by its value found previously, on the column ...
	            x.tabElement.set(j, x.tabElement.get(j) - value); // ... and we move this value on the side of b to leave only the variables in the A matrix.
	        }
	    }
		
	}


	private void solveTriangularSystemDown(vector x, tridiagonalMatrix A, vector b) {
		double value;
	    x.tabElement.set(0, b.tabElement.get(0));

	    for(int i = 1 ; i <= A.lenght ; i++) {
	        value = b.tabElement.get(i);
	        for (int j = 0; j <= i; j++) {
	            value -= A.matrix[i*A.lenght+j]*x.tabElement.get(j);
	        }
	        x.tabElement.set(i, value);
	   }
	
	}
	
	
	private void decompositionLU(tridiagonalMatrix A) {
		double coef;
		
		for (int cl = 0; cl < A.lenght - 1; cl++) {
	        for (int lgn = cl + 1; lgn < A.lenght; lgn++) {
	            // if the coef is not null
	            if (A.matrix[cl * A.lenght + cl] != 0) {
	                // determine the coef x (exp L2 = L2 - xL1)
	                 coef = A.matrix[lgn * A.lenght + cl] / A.matrix[cl * A.lenght + cl];
	                // performs the calculation (L2 = L2-xL1) by applying x to each cell of the line

	                for (int w = cl; w < A.lenght; w++) {
	                    A.matrix[lgn * A.lenght + w] = A.matrix[lgn * A.lenght + w] - coef * A.matrix[cl * A.lenght + w];
	                }

	                A.matrix[lgn * A.lenght + cl] =  coef;
	            }
	        }
	    }
		
	}
	
	public tridiagonalMatrix copy() {
		return new tridiagonalMatrix(this.lenght, this.matrix);
	}

}
