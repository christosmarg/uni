import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class UseCase1_Main {
    public static void main(String[] args) throws IOException {
        Booker booker = new Booker();
        Scanner sc = new Scanner(System.in);

        System.out.println("Hello client, please enter your info :");
        ClientInfo c = booker.GetClientInfo();

        String []IDs = booker.SearchFlight();
		while (IDs == null) {
			System.out.println("Flight not found");
			System.out.println("Do you wish to search for another flight? (Y/N)");
			String ans = sc.nextLine();
			if (!(ans.equals("Y") || ans.equals("y"))) { System.out.println("Goodbye!"); return; }
			IDs = booker.SearchFlight();
		}

		Ticket t = booker.Database.BookSeat(c, Integer.parseInt(IDs[0]), IDs[1]);
		booker.PrintTicket(t);

		System.out.println("Ticket booked!");
		System.out.println("Have a nice day!");

		try
		{
			booker.Database.SaveDB("DataBase.db");
			System.out.println("Ticket data saved.");
		}
		catch (IOException e)
		{
			System.out.println("Ticket data save failed (Insufficient permissions?)");
		}

    }
}