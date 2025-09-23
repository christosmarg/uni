package population;

import java.util.HashMap;

public class Country {
	private String index;;
	private String variant = "";
	private String name = "";
	private String notes = "";
	private String ctrycode;
	private String type = "";
	private String pntcode;
	private HashMap<Integer, Integer> population;
	private Integer recentpop;
	
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
		recentpop = population.get(population.size());
	}
	
	public String get_index() {
		return index;
	}
	
	public String get_variant() {
		return variant;
	}
	
	public String get_name() {
		return name;
	}
	
	public String get_notes() {
		return notes;
	}
	
	public String get_ctrycode() {
		return ctrycode;
	}
	
	public String get_type() {
		return type;
	}
	
	public String get_pntcode() {
		return pntcode;
	}
	
	public HashMap<Integer, Integer> get_population() {
		return population;
	}
}
