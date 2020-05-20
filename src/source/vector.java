package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    protected ArrayList<Double> tabElement;

    //Constructor 1
    public vector(int numberElement, double tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = new ArrayList<Double>();
        this.initTab(tabElement);
    }

    //Constructor 2
    public vector() {
        this.numberElement = 0;
        this.tabElement = new ArrayList<Double>();
    }

    /**
     * @role : Initialize array of element of "this".
     * @param tabElement
     */
    public void initTab(double tabElement[]) {
        for (int i = 0 ; i < this.numberElement ; ++i) {
            this.getTabElement().add(tabElement[i]);
        }
    }

    /**
     * @role : Insert element in "tabElement".
     * @param i :
     * @param value :
     */
    public void insert(int i, double value) {
        this.getTabElement().remove(i);
        this.getTabElement().add(i, value);
    }

    /**
     * @role : This function uses to get array of element.
     * @return ArrayList<Double>
     */
	public ArrayList<Double> getTabElement() {
		return tabElement;
	}


}
