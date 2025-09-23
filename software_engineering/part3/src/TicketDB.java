import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.File;
import java.util.ArrayList;
import java.util.Scanner;

public class TicketDB {
    public ArrayList<Flight> AllFlights;

    public ArrayList<Ticket> AllTickets;
	
	public TicketDB() throws FileNotFoundException {
        AllFlights = new ArrayList<>();
        AllTickets = new ArrayList<>();


        // "load" flights (they are given as constants for demo purposes)

        // causing a weird bug due to all flights getting the same "pointer" for their seats
        // so we create different object for each flight demo

		Seat s1 = new Seat(false, 1);
		Seat s2 = new Seat(false, 2);
		Seat s3 = new Seat(false, 3);

        Seat s1_2 = new Seat(false, 1);
        Seat s2_2 = new Seat(false, 2);
        Seat s3_2 = new Seat(false, 3);

        Seat s1_3 = new Seat(false, 1);
        Seat s2_3 = new Seat(false, 2);
        Seat s3_3 = new Seat(false, 3);

        Seat s1_4 = new Seat(false, 1);
        Seat s2_4 = new Seat(false, 2);
        Seat s3_4 = new Seat(false, 3);

        Seat s1_5 = new Seat(false, 1);
        Seat s2_5 = new Seat(false, 2);
        Seat s3_5 = new Seat(false, 3);

		Seat []seats1 = {s1,s2,s3};
        Seat []seats2 = {s1_2,s2_2,s3_2};
        Seat []seats3 = {s1_3,s2_3,s3_3};
        Seat []seats4 = {s1_4,s2_4,s3_4};
        Seat []seats5 = {s1_5,s2_5,s3_5};


		AllFlights.add(new Flight(seats1, "Monaco", "Barcelona", "05/31/22", "052A"));
        AllFlights.add(new Flight(seats2, "Monaco", "Barcelona", "06/01/22", "053A"));
		AllFlights.add(new Flight(seats3, "Barcelona", "Mexico", "06/05/22", "062A"));
		AllFlights.add(new Flight(seats4, "UK", "Greece", "07/05/22", "072A"));
        AllFlights.add(new Flight(seats5, "UK", "Greece", "07/06/22", "073A"));

        // load Tickets from file

        try
        {
            LoadDB("DataBase.db");
        }
        catch (FileNotFoundException e)
        {
            System.out.println("! Database file not found, no tickets loaded.");
        }

	}

	public void LoadDB(String path) throws FileNotFoundException {
        File fileObj = new File(path);
        Scanner reader = new Scanner(fileObj);
        while (reader.hasNextLine()) {
            String data = reader.nextLine();
            String []ticketData = data.split("-");
            ClientInfo c = new ClientInfo(ticketData[3], ticketData[4],
                    ticketData[5], ticketData[6], ticketData[7]);
            Ticket T = new Ticket(c, ticketData[0], Integer.parseInt(ticketData[1]), ticketData[2]);

            for (Flight f : AllFlights)
            {
                if (T.FlightID.equals(f.ID))
                {
                    f.Seats[T.SeatID-1].isOccupied = true;
                    break;
                }
            }
            AllTickets.add(T);
        }
        reader.close();
    }

    public void SaveDB(String path) throws IOException {
        FileWriter fileObj = new FileWriter(path);
        for (Ticket T : AllTickets)
            fileObj.write(T.toDataString() + "\n");
        fileObj.close();
    }

    public ArrayList<Seat> CheckFlight(Flight F) {
        ArrayList<Seat> seats = new ArrayList<>();
        
        for (Seat s : F.Seats) {
            if (!s.isOccupied)
                seats.add(s);
        }
        if (seats.size() > 0)
            return seats;
        else
            return null;
    }

    public Ticket BookSeat(ClientInfo CInfo, int SeatInd, String fID) {
        for (Flight f : AllFlights) {
            if (f.ID.equals(fID)) {
                f.Seats[SeatInd-1].isOccupied = true;
				String seatid = Integer.toString(f.Seats[SeatInd-1].ID);
				Ticket t = new Ticket(CInfo, fID, SeatInd, fID + seatid);
				AllTickets.add(t);
				return t;
            }
        }
		
		return null;
    }

    public boolean CheckTicket(Ticket T) {
		for (Ticket Check : AllTickets)
		    if (Check.TicketID.equals(T.TicketID))
		        return true;
	    return false;
    }

}
