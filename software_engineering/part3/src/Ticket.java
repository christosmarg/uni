public class Ticket {
    public String TicketID;

    public ClientInfo Holder;

    public int SeatID;

    public String FlightID;

    public Ticket(ClientInfo Holder_, String FlightID_, int SeatID_, String TicketID_) {
		Holder = Holder_;
		FlightID = FlightID_;
		SeatID = SeatID_;
		TicketID = TicketID_;
    }
	
	public String toString()
	{
		String s = "Ticket info:\n";
		s += "Seat ID : " + Integer.toString(SeatID) + "\n";
		s += "Flight ID : " + FlightID + "\n";
		s += "Holder info : \n" + Holder.toString();

		return s;
	}

	public String toDataString()
	{
		return FlightID + "-" + SeatID + "-" + TicketID
				+ "-" + Holder.FullName + "-" + Holder.Phone
				+ "-" + Holder.BirthDate + "-" + Holder.CreditCard
				+ "-" + Holder.Address;
	}

}
