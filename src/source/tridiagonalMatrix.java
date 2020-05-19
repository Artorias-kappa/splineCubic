package source;

public class tridiagonalMatrix {
	private int lenght;
	private float middleDiagonalCoef;
	private float lowDiagonalCoef;
	private float hightDiagonalCoef;
	
	public tridiagonalMatrix(int lenght, float middleDiagonalCoef, float lowDiagonalCoef, float hightDiagonalCoef) {
		
		this.lenght = lenght;
		this.middleDiagonalCoef = middleDiagonalCoef;
		this.lowDiagonalCoef = lowDiagonalCoef;
		this.hightDiagonalCoef = hightDiagonalCoef;
		
	}
	
	public vector resolvSystem(vector b) {
		
		return new vector();
	}
}
