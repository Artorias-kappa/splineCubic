package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    protected double tabElement[];


    //Constructor 1
    public vector(int numberElement, double tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = new double[numberElement];
    }

    //Constructor 2
    public vector() {
        this.numberElement = 0;
        this.tabElement = null;
    }

    /**
     * @role : Initialize array of element of "this".
     * @param tabElement
     */
    public void initTab(double tabElement[]) {
            this.tabElement = tabElement;
        
    }

    /**
     * @role : Insert element in "tabElement".
     * @param i :
     * @param value :
     */
    public void insert(int i, double value) {
        this.getTabElement()[i] = value;
    }


    /**
     * @role : This function uses to get array of element.
     * @return ArrayList<Double>
     */
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
