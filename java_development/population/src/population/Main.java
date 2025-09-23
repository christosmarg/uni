package population;

import java.io.*;
import java.util.List;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Main extends Application {
	private final String APP_TITLE = "Population Statistics";
	List<Country> countries;
	
	@Override
	public void start(Stage primstage) throws Exception {
		Parameters params;
		List<String> args;
		ExcelParser ep;
		String path = "";
		
		/* Parse Excel file. */
		params = getParameters();
		args = params.getRaw();
		try {
			path = args.get(0);
			ep = new ExcelParser(path);
		} catch (FileNotFoundException e) {
			err(primstage, path + ": no such file");
			return;
		} catch (IndexOutOfBoundsException e) {
			err(primstage, "usage: population xlsx_file");
			return;
		} catch (IOException e) {
			err(primstage, path + ": io error");
			return;
		}
		countries = ep.get_countries();
		
		/* Set up GUI. */
	}
	
	/* TODO: make it an actual popup error window. */
	public void err(Stage stg, String errstr) {
		Label lbl = new Label(errstr);
		Scene scene = new Scene(new StackPane(lbl), 300, 200);
		
		stg.setScene(scene);
		stg.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}