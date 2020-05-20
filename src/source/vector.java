package source;

import java.util.ArrayList;

public class vector {
    private int numberElement;
    protected ArrayList<Double> tabElement;


    public vector(int numberElement, double tabElement[]) {
        this.numberElement = numberElement;
        this.tabElement = new ArrayList<Double>();
        this.initTab(tabElement);
    }

    public vector() {
        this.numberElement = 0;
        this.tabElement = new ArrayList<Double>();
    }

    public void initTab(double tabElement[]) {
        for (int i = 0 ; i < this.numberElement ; ++i) {
            this.getTabElement().add(tabElement[i]);
        }
    }

    public void insert(int i, double value) {
        this.getTabElement().remove(i);
        this.getTabElement().add(i, value);
    }

	public ArrayList<Double> getTabElement() {
		return tabElement;
	}


}
