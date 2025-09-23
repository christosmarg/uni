package population;

public class Column {
	private String name;
	private String fieldname;
	
	Column(String name, String fieldname) {
		this.name = name;
		this.fieldname = fieldname;
	}
	
	public String get_name() {
		return name;
	}
	
	public String get_fieldname() {
		return fieldname;
	}
}
