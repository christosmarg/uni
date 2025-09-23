package population;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableRow;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Main extends Application {
	public static final int STARTING_YEAR = 1950;
	private final String APP_TITLE = "Population Statistics";
	List<Country> countries;
	
	@Override
	public void start(Stage stg) throws Exception {
		Parameters params;
		List<String> args;
		ExcelParser ep;
		String path = "";
		VBox vb;
		HBox btns;
		TableView<Country> tbv;
		
		/* Parse Excel file. */
		params = getParameters();
		args = params.getRaw();
		try {
			path = args.get(0);
			ep = new ExcelParser(path);
		} catch (FileNotFoundException e) {
			err(stg, path + ": no such file");
			return;
		} catch (IndexOutOfBoundsException e) {
			err(stg, "usage: population xlsx_file");
			return;
		} catch (IOException e) {
			err(stg, path + ": io error");
			return;
		}
		countries = ep.get_countries();
		
		/* Set up GUI. */
		tbv = mktable(stg);
		btns = mkbtns();
		vb = mkvbox(tbv, btns);
		stg.setTitle(APP_TITLE);
		stg.setScene(new Scene(vb));
		stg.show();
	}
	
	/* TODO: make it an actual popup error window? */
	private void err(Stage stg, String errstr) {
		Label lbl = new Label(errstr);
		lbl.setAlignment(Pos.CENTER);
		Scene scene = new Scene(lbl);
		
		stg.setScene(scene);
		stg.show();
	}
	
	private HBox mkbtns() {
		HBox hb;
		Button btn_chart;
		Button btn_exit;
		
		hb = new HBox();
		btn_exit = new Button("Exit");
		btn_exit.setOnAction(value -> {
			Platform.exit();
			System.exit(0);
		});
		btn_chart = new Button("Chart");
		btn_chart.setOnAction(value -> {
			mkchart();
		});
		hb.getChildren().addAll(btn_chart, btn_exit);
		hb.setSpacing(5);
		hb.setAlignment(Pos.CENTER);
		return hb;
	}
	
	private TableView<Country> mktable(Stage stg) {
		TableView<Country> tbv;
		TableColumn<Country, String> tbc;
		List<Column> cols;
		ObservableList<Country> addrs;
		
		cols = new ArrayList<Column>(Arrays.asList(
		    new Column("Index", "index"),
		    new Column("Variant", "variant"),
		    new Column("Country", "name"),
		    new Column("Notes", "notes"),
		    new Column("Country Code", "ctrycode"),
		    new Column("Type", "type"),
		    new Column("Parent Code", "pntcode"),
		    new Column("Population", "recentpop")
		));
		tbv = new TableView<Country>();
		addrs = FXCollections.observableArrayList(countries);
		for (Column col : cols) {
			tbc = new TableColumn<Country, String>(col.get_name());
			tbc.setCellValueFactory(
			    new PropertyValueFactory<Country, String>(
			    col.get_fieldname()));
			tbv.getColumns().add(tbc);
		}
		tbv.setRowFactory(tv -> {
			TableRow<Country> row = new TableRow<Country>();
			row.setOnMouseClicked(ev -> {
				if (ev.getClickCount() == 2 && !row.isEmpty()) {
					Country c = row.getItem();
					/* TODO: implement toast */
					System.out.println(
					    c.getIndex() + "," +
					    c.getName() + "," + 
					    c.getRecentpop());
				}
			});
			return row;
		});
		tbv.setItems(addrs);
		tbv.prefWidthProperty().bind(stg.widthProperty());
		tbv.prefHeightProperty().bind(stg.heightProperty());
		return tbv;
	}
	
	private VBox mkvbox(TableView<Country> tbv, HBox btns) {
		VBox vb;
		
		vb = new VBox();
		vb.setSpacing(5);
		vb.setPadding(new Insets(10, 10, 10, 10));
		vb.getChildren().addAll(tbv, btns);
		return vb;
	}
	
	private void mkchart() {
		
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}