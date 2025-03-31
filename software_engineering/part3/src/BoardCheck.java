import java.io.FileNotFoundException;
import java.util.ArrayList;

public class BoardCheck
{
    TicketDB Database;
    MetalDetector Detector;

    public BoardCheck() throws FileNotFoundException
    {
        Database = new TicketDB();
        Detector = new MetalDetector(1, 0.5f);
    }


    public boolean CanBoard(Ticket T, ArrayList<Item>Items)
    {
        if (!Database.CheckTicket(T))
        {
            System.out.println("Invalid ticket.");
            return false;
        }
        if (!Detector.ScanPassenger(Items))
        {
            System.out.println("Detected amount of metal exceeding mass threshold");
            System.out.println(Detector.PreviousScans.get(Detector.PreviousScans.size() - 1)
                + "kg of metallic material detected on scan.");
            return false;
        }

        System.out.println("Ticket is valid.");
        System.out.println("Detected amount of metal is under mass threshold");
        System.out.println(Detector.PreviousScans.get(Detector.PreviousScans.size() - 1)
                + "kg of metallic material detected on scan.");
        return true;
    }
}
