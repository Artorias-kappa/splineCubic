package main;


public class main {




	public static void main(String[] args) {
		
		int sizeTest = 4;
		

		double[] test = initTab(sizeTest);

		System.out.println(display(test, sizeTest));






	}

	public static double[] initTab(int size) {
		double[] newList = new double[size * size];

		for (int i = 0 ; i < size ; ++i) {
			for (int j = 0 ; j < size ; ++j) {
				if (i == j && i < size - 1) {
					newList[i * size + j] = 4;
					newList[(i + 1) * size + j] = 1;
					newList[i * size + (j + 1)] = 1;
				}
			}
		}
		newList[size * size - 1] = 4;
		return newList;
	}

	public static String display(double[] list, int size) {

		String display = "";

		for (int i = 0 ; i < size ; ++i) {
			for (int j = 0 ; j < size ; ++j) {
				display += list[i * 4 + j] + " ";
			}
			display += "\n";
		}
		return display;
	}



}



