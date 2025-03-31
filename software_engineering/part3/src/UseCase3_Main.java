import java.io.IOException;

public class UseCase3_Main {
    public static void main(String[] args) throws IOException {
        FIDS_DB fids_database = new FIDS_DB();
        fids_database.updateDB();
        fids_database.parseData();
        fids_database.showData();
    }
}
