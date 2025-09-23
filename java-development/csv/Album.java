class Album {
	private String title;
	private String artist;
	private Integer year;
	private Float price;

	Album(String title, String artist, Integer year, Float price) {
		this.title = title;
		this.artist = artist;
		this.year = year;
		this.price = price;
	}

	public String get_title() {
		return title;
	}

	public String get_artist() {
		return artist;
	}

	public Integer get_year() {
		return year;
	}

	public Float get_price() {
		return price;
	}

	@Override
	public String toString () {
		return String.format("%-40s\t", title) +
		    String.format("%-30s\t", artist) +
		    year + "\t" + price;
	}
}
