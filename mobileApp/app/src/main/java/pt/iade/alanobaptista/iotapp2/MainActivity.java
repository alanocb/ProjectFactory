package pt.iade.alanobaptista.iotapp2;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private TextView temperatureTextView;
    private TextView humidityTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        temperatureTextView = findViewById(R.id.temperatureTextView);
        humidityTextView = findViewById(R.id.humidityTextView);
        Button refreshButton = findViewById(R.id.refreshButton);

        Button buttonLigar = findViewById(R.id.buttonLigar);
        Button buttonDesligar = findViewById(R.id.buttonDesligar);
        Button rgbRed = findViewById(R.id.rgbRed);
        Button rgbGreen = findViewById(R.id.rgbGreen);
        Button rgbBlue = findViewById(R.id.rgbBlue);
        Button rgbOff = findViewById(R.id.rgbOff);

        buttonLigar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TurnOnLEDTask turnOnLEDTask = new TurnOnLEDTask();
                turnOnLEDTask.execute();
                Log.d("LED", "botao ligar");
            }
        });

        buttonDesligar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TurnOffLEDTask turnOffLEDTask = new TurnOffLEDTask();
                turnOffLEDTask.execute();
                Log.d("LED", "botao desligar");
            }
        });

        rgbRed.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new setRgb(255, 0, 0).execute(); // Set the LED to red
            }
        });

        rgbGreen.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new setRgb(0, 255, 0).execute(); // Set the LED to green
            }
        });

        rgbBlue.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new setRgb(0, 0, 255).execute(); // Set the LED to blue
            }
        });

        rgbOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new setRgb(0, 0, 0).execute(); // Turn off the LED
            }
        });

        refreshButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new GetEnvironmentDataTask(temperatureTextView, humidityTextView).execute();
            }
        });
    }
}
