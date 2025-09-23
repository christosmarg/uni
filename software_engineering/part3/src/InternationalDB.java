import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

public class InternationalDB {
    public String sourceUrl = "https://opensky-network.org/api/states/all?lamin=30.038&lomin=-125.974&lamax=52.214&lomax=-68.748";

    public String locPath = "InternationalFlightTracking.db";

    public int sizeLimit = 2; // limit file size in KB

    public void downloadData() throws IOException {
        try (BufferedInputStream inputStream = new BufferedInputStream(new URL(sourceUrl).openStream());
             FileOutputStream fileOS = new FileOutputStream(locPath)) {
            byte[] data = new byte[1024];
            int byteContent;


            int size = 0;
            while (((byteContent = inputStream.read(data, 0, 1024)) != -1 ) && size < sizeLimit) {
                fileOS.write(data, 0, byteContent);
                size++;
            }
        } catch (IOException e) {
            System.out.println("No file permissions");
        }
    }
}
