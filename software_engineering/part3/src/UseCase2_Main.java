import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class UseCase2_Main
{
    public static void main(String[] args) throws FileNotFoundException {
        BoardCheck PlaneCheck = new BoardCheck();
        Scanner sc = new Scanner(System.in);

        // Passengers items are somehow scanned in a physical metal detector
        ArrayList<Item> PassengerItems = new ArrayList<>();
        PassengerItems.add(new Item("Metal", 0.1f, "Keys"));
        PassengerItems.add(new Item("Iron", 0.2f, "Coins"));
        PassengerItems.add(new Item("Plastic", 0.3f, "Phone"));
        PassengerItems.add(new Item("Leather", 0.2f, "Belt"));

        // Passengers ticket is scanned by personnel
        System.out.println("Enter ticket info");
        System.out.println("Enter flight ID : ");
        String fID = sc.nextLine();
        System.out.println("Enter Seat ID : ");
        String sID = sc.nextLine();
        System.out.println("Enter Ticket ID : ");
        String tID = sc.nextLine();

        Ticket PassengerTicket = new Ticket(null, fID, Integer.parseInt(sID), tID);

        if (PlaneCheck.CanBoard(PassengerTicket, PassengerItems))
            System.out.println("You may board the plane.");
        else
            System.out.println("You may not board the plane.");
    }
}
