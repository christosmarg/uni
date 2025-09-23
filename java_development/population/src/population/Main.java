package population;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {
	private final String APP_TITLE = "Population Statistics";
	
	@Override
	public void start(Stage stg) {
		MainWindow mw = new MainWindow(stg, APP_TITLE);
		
		try {
			mw.setup(getParameters().getRaw().get(0));
		} catch (IndexOutOfBoundsException e) {
			mw.err("usage: population xlsx_file");
			return;
		}
		mw.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}