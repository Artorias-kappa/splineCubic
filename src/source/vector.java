package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    protected double tabElement[];


    public vector(int numberElement) {
        this.numberElement = numberElement;
        this.tabElement = new double[numberElement];
    }

    public void insert(int i, double value) {
        this.getTabElement()[i] = value;
    }

	public double[] getTabElement() {
		return tabElement;
	}


}
