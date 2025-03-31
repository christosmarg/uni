public class Seat {
    public boolean isOccupied;

    public int ID;

    public Flight flight;

    public Seat(boolean isOccupied_, int ID_) {
		ID = ID_;
		isOccupied = isOccupied_;
    }
	public String toString()
	{
		return "Seat ID : " + ID;
	}

}
