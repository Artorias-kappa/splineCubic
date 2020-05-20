package main;

import source.*;

public class main {



	public static void main(String[] args) {
		
		int sizeTest = 4;
		
		double test[] = {
				4, 1, 0, 0,
				1, 4, 1, 0,
				0, 1, 4, 1,
				0, 0, 1, 4
		};
		
		double b[] = {
				3,
				2,
				4,
				1
		};
		
		
		tridiagonalMatrix matrixtest = new tridiagonalMatrix(sizeTest, test);
		vector vectortest = new vector(sizeTest, b);
		vector solution = new vector(sizeTest);
		
		vectortest.vectorAff();
		matrixtest.matrixAff();
		solution = matrixtest.solveSystemLU(vectortest);
		solution.vectorAff();




	}

}
