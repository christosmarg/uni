class Movie {
	private String title;
	private Integer year;
	private Float price;

	Movie(String title, Integer year, Float price) {
		this.title = title;
		this.year = year;
		this.price = price;
	}

	public String get_title() {
		return title;
	}

	public Integer get_year() {
		return year;
	}

	public Float get_price() {
		return price;
	}

	@Override
	public String toString () {
		return String.format("%-20s\t", title) + year + "\t" + price;
	}
}
