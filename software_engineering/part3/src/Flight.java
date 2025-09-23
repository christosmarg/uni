public class Flight {
    public Seat[] Seats;

    public String StartingPoint;

    public String Destination;

    public String Date_;

    public String ID;

	public Flight(Seat[] Seats_, String start, String dest, String D, String ID_)
	{
		Seats = Seats_;
		StartingPoint = start;
		Destination = dest;
		Date_ = D;
		ID = ID_;
	}

	public String toString()
	{
		return  "Flight starting point : " + StartingPoint + "\n"
				+ "Flight destination : " + Destination + "\n"
				+ "Flight Date : " + Date_ + "\n"
				+ "Flight ID : " + ID + "\n";
	}
}
