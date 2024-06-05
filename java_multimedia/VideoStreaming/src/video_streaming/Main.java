package video_streaming;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Main extends Application {
	@Override
	public void start(Stage stg) throws Exception {
		stg.setTitle("Video Streaming Client");
	        stg.setScene(new Scene(new StackPane(), 350, 230));
	        stg.show();
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
