package population;

import java.util.HashMap;

public class Country {
	private String index = "";
	private String variant = "";
	private String name = "";
	private String notes = "";
	private String ctrycode = "";
	private String type = "";
	private String pntcode = "";
	private HashMap<String, String> population;

	public void add_population(String k, String v) {
		population.put(k, v);
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
}
