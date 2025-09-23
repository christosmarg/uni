import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Booker {
    public TicketDB Database;
    Scanner sc;
    Flight fl;
    
    Booker() throws FileNotFoundException {
        sc = new Scanner(System.in);
		Database = new TicketDB();
    }

    public ClientInfo GetClientInfo() {
        System.out.print("name: ");
        String name = sc.nextLine();
        
        System.out.print("tel: ");
        String tel = sc.nextLine();
        
        System.out.print("birth date: ");
        String bdate = sc.nextLine();
        
        System.out.print("credit card: ");
        String card = sc.nextLine();
        
        System.out.print("address: ");
        String addr = sc.nextLine();
        
        return new ClientInfo(name, tel, bdate, card, addr);
    }

    public String[] SearchFlight() {
        System.out.println("Please enter details of your desired flight");
        System.out.println("starting point: ");
        String start = sc.nextLine();

        System.out.println("destination: ");
        String dest = sc.nextLine();

        ArrayList<Flight> ExistingFlights = new ArrayList<>();
        ArrayList<Flight> AvailableFlights = new ArrayList<>();
        for (Flight f : Database.AllFlights)
        {
            if (f.StartingPoint.equals(start) && f.Destination.equals(dest))
                ExistingFlights.add(f);
        }

        for (Flight f : ExistingFlights)
        {
            if (Database.CheckFlight(f) != null)
                AvailableFlights.add(f);
        }

        if (AvailableFlights.size() == 0)
            return null;

        System.out.println("Available flights are : ");

        for (Flight f : AvailableFlights)
        {
            System.out.println(f.toString());
            System.out.println("--------------");
        }

        System.out.println("Enter desired flight ID : ");
        String fID = sc.nextLine();

        boolean found = false;
        for (Flight f : AvailableFlights) {
            if (f.ID.equals(fID)) {
                found = true;
                fl = f;
                break;
            }
        }
        while(!found)
        {
            System.out.println("Invalid Flight ID, Please try again : ");
            fID = sc.nextLine();
            for (Flight f : AvailableFlights) {
                if (f.ID.equals(fID)) {
                    found = true;
                    fl = f;
                    break;
                }
            }
        }

        ArrayList<Seat> seats = Database.CheckFlight(fl);

        System.out.println("Available seats are : ");

        for (Seat s : seats)
            System.out.println(s.toString());

        System.out.println("Enter ID of desired seat : ");
        int sID = sc.nextInt();
        while (!ValidSeat(sID))
        {
            System.out.println("Invalid selection! Please try again :");
            sID = sc.nextInt();
        }

        return new String[]{Integer.toString(sID),fID};
    }

    public void PrintTicket(Ticket T) {
        System.out.println(T.toString());
    }

    public boolean ValidSeat(int SeatInd) {
        if (SeatInd > fl.Seats.length || SeatInd < 1)
            return false;
        return !fl.Seats[SeatInd-1].isOccupied;
    }

}
