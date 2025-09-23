import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class FIDS_DB {
    public ArrayList<FlightInfo> FlightsArr;
    public InternationalDB InternationalFT;
    public int parseLimit = 2;

    public FIDS_DB()
    {
        FlightsArr = new ArrayList<>();
        InternationalFT = new InternationalDB();
    }

    public void updateDB() throws FileNotFoundException {
        try {
            InternationalFT.downloadData();
        } catch (IOException e) {
            System.out.println("No internet connection.");
        }

        FlightsArr = parseData();

    }

    public ArrayList<FlightInfo> parseData() throws FileNotFoundException {
        ArrayList<FlightInfo> data = new ArrayList<>();

        File fileObj = new File(InternationalFT.locPath);
        Scanner reader = new Scanner(fileObj);
        while (reader.hasNextLine()) {
            String dat = reader.nextLine();


            String []p1 = dat.split("\\[\\[");
            for (int i = 1; i <= parseLimit; i++)
            {
                String []p2 = p1[1].split(",");

                FlightInfo f = new FlightInfo(p2[1], p2[2], p2[3], p2[5], p2[6], p2[7]);
                data.add(f);

                p1 = p1[1].split("],\\[");
            }
        }

        return data;
    }

    public void showData()
    {
        System.out.println("F.I.D.S.");
        System.out.println("--------");
        for (FlightInfo f : FlightsArr)
        {
            System.out.println("Origin country : " + f.originCountry);
            System.out.println("Flight code : " + f.flightCode);
            System.out.println("Latitude : " + f.lat);
            System.out.println("Longtitude : " + f.lng);
            System.out.println("Timepos : " + f.timePos);
            System.out.println("Velocity : " + f.velocity);
            System.out.println("--------");
        }
    }
}
