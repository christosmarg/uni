package population;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {
	private final String APP_TITLE = "Population Statistics";
	
	@Override
	public void start(Stage stg) throws Exception {
		MainWindow mw = new MainWindow(stg, APP_TITLE);

		mw.setup(getParameters().getRaw().get(0));
		mw.show();
	}

	public static void main(String[] args) {
		launch(args);
	}
}