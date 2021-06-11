package population;

import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

public class Toast {
	private final int WIDTH_MARGIN = 20;
	private final int HEIGHT = 50;
	private final int FADEOUT_DUR = 500;
	private final int FADEIN_DUR = 500;
	private final int TOAST_DUR = 2500;
	private final int FONT_SIZE = 14;
	private final String FONT = "Verdana";
	private Stage stg;
	private Text txt;
	private String style;
	
	Toast(Country ctry, Stage owner) {
		stg = new Stage();
		txt = new Text(ctry.getIndex() + ", " + 
		    ctry.getName() + ", " +
		    ctry.getCurpop());
		style = "-fx-background-radius: 20;" +
			"-fx-background-color: rgba(0, 0, 0, 0.18);" +
			"-fx-padding: 50px;";
		
	        txt.setFill(Color.BLUE);
	        txt.setFont(Font.font(FONT, FontWeight.BOLD, FONT_SIZE));
	        stg.setWidth(txt.getLayoutBounds().getWidth() + WIDTH_MARGIN);
	        stg.setHeight(HEIGHT);
		stg.setResizable(false);
		stg.initOwner(owner);
		stg.initStyle(StageStyle.TRANSPARENT);
	}
	
	public void show() {
		StackPane root = new StackPane(txt);
		Scene scene = new Scene(root);
		Timeline fintml;
		KeyFrame finkey;
	        
		root.setStyle(style);
		root.setOpacity(0);
		scene.setFill(Color.TRANSPARENT);
		stg.setScene(scene);
		stg.show();
		fintml = new Timeline();
		finkey = new KeyFrame(Duration.millis(FADEIN_DUR),
		    new KeyValue(stg.getScene().getRoot().opacityProperty(), 1));
		fintml.getKeyFrames().add(finkey);  
		fintml.setOnFinished(ev -> closing_animation()); 
		fintml.play();
	}
	
	private void closing_animation() {
		new Thread(() -> {
			try {
				Thread.sleep(TOAST_DUR);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			Timeline fouttml = new Timeline();
			KeyFrame foutkey = 
			    new KeyFrame(Duration.millis(FADEOUT_DUR),
			    new KeyValue(stg.getScene()
			        .getRoot()
			        .opacityProperty(), 0)); 
			fouttml.getKeyFrames().add(foutkey);   
			fouttml.setOnFinished(e -> stg.close());
			fouttml.play();
		}).start();
	}
}
