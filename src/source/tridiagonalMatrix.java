package source;

public class tridiagonalMatrix {
	private int lenght;
	private double middleDiagonalCoef;
	private double lowDiagonalCoef;
	private double hightDiagonalCoef;
	
	public tridiagonalMatrix(int lenght, double middleDiagonalCoef, double lowDiagonalCoef, double hightDiagonalCoef) {
		
		this.lenght = lenght;
		this.middleDiagonalCoef = middleDiagonalCoef;
		this.lowDiagonalCoef = lowDiagonalCoef;
		this.hightDiagonalCoef = hightDiagonalCoef;
		
	}
	
	public vector resolvSystem(vector b) {
		return new vector();
	}


}
