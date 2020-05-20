package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    protected double tabElement[];


    public vector(int numberElement) {
        this.numberElement = numberElement;
        this.tabElement = new double[numberElement];
    }
    
    public vector(int numberElement, double tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = tabElement;
    }

    public void insert(int i, double value) {
        this.getTabElement()[i] = value;
    }

	public double[] getTabElement() {
		return tabElement;
	}
	
	/**
	 * @role : displays a matrix in the form of an array n x n.
	 * 
	 */
	public void vectorAff() {
	    for (int i = 0; i < numberElement; i++) {
	        System.out.print(tabElement[i]+"\t");
	        System.out.print("\n");
	    }
	    System.out.print("\n");
	}


}
