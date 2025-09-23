package population;

import java.util.HashMap;

public class Country {
	private String index;
	private String variant = "";
	private String name = "";
	private String notes = "";
	private String ctrycode;
	private String type = "";
	private String pntcode;
	private HashMap<Integer, Integer> population;
	private String recentpop;
	
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
		recentpop = String.valueOf(
		   population.get(Main.STARTING_YEAR + population.size() - 1));
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
	
	public String getRecentpop() {
		return recentpop;
	}
}
