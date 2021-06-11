package population;

import java.util.HashMap;

public class Country {
	public static final int STARTING_YEAR = 1950;
	public static int LAST_YEAR;
	private String index;
	private String variant = "";
	private String name = "";
	private String notes = "";
	private String ctrycode;
	private String type = "";
	private String pntcode;
	private HashMap<Integer, Integer> population;
	private String curpop;

	Country(String index, String variant, String name, String notes,
	    String ctrycode, String type, String pntcode,
	    HashMap<Integer, Integer> population) {
		this.index = index;
		this.variant = variant;
		this.name = name;
		this.notes = notes;
		this.ctrycode = ctrycode;
		this.type = type;
		this.pntcode = pntcode;
		this.population = population;
		LAST_YEAR = STARTING_YEAR + this.population.size() - 1;
		setCurpop(LAST_YEAR);

	}
	
	/* 
	 * The getters *must* have this naming convention, otherwise 
	 * JavaFX TableView methods don't recognize them. Pretty stupid...
	 */
	public String getIndex() {
		return index;
	}
	
	public String getVariant() {
		return variant;
	}
	
	public String getName() {
		return name;
	}
	
	public String getNotes() {
		return notes;
	}
	
	public String getCtrycode() {
		return ctrycode;
	}
	
	public String getType() {
		return type;
	}
	
	public String getPntcode() {
		return pntcode;
	}
	
	public HashMap<Integer, Integer> getPopulation() {
		return population;
	}
	
	public String getCurpop() {
		return curpop;
	}
	
	public void setCurpop(Integer i) {
		curpop = String.valueOf(population.get(i));
	}
}
