package pt.iade.alanobaptista.iotapp2;

import android.os.AsyncTask;
import android.widget.TextView;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

public class GetEnvironmentDataTask extends AsyncTask<Void, Void, JSONObject> {

    private static final String API_URL_TEMPERATURE = "http://10.0.2.2:3000/temperature";
    private static final String API_URL_HUMIDITY = "http://10.0.2.2:3000/humidity";

    private TextView temperatureTextView;
    private TextView humidityTextView;

    public GetEnvironmentDataTask(TextView temperatureTextView, TextView humidityTextView) {
        this.temperatureTextView = temperatureTextView;
        this.humidityTextView = humidityTextView;
    }

    @Override
    protected JSONObject doInBackground(Void... voids) {
        OkHttpClient client = new OkHttpClient();

        try {
            Request requestTemp = new Request.Builder()
                    .url(API_URL_TEMPERATURE)
                    .get()
                    .build();

            Request requestHum = new Request.Builder()
                    .url(API_URL_HUMIDITY)
                    .get()
                    .build();

            Response responseTemp = client.newCall(requestTemp).execute();
            Response responseHum = client.newCall(requestHum).execute();

            if (responseTemp.isSuccessful() && responseHum.isSuccessful()) {
                ResponseBody responseBodyTemp = responseTemp.body();
                ResponseBody responseBodyHum = responseHum.body();

                String responseStringTemp = responseBodyTemp.string();
                String responseStringHum = responseBodyHum.string();

                JSONObject jsonObjectTemp = new JSONObject(responseStringTemp);
                JSONObject jsonObjectHum = new JSONObject(responseStringHum);

                JSONObject result = new JSONObject();
                result.put("temperature", jsonObjectTemp.getString("temperature"));
                result.put("humidity", jsonObjectHum.getString("humidity"));

                return result;
            }
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onPostExecute(JSONObject result) {
        super.onPostExecute(result);
        if (result != null) {
            try {
                String temperature = result.getString("temperature");
                String humidity = result.getString("humidity");

                // Format the temperature to one decimal place
                double tempValue = Double.parseDouble(temperature);
                String formattedTemperature = String.format("%.1f", tempValue);

                temperatureTextView.setText("Temperature: " + formattedTemperature);
                humidityTextView.setText("Humidity: " + humidity);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
    }
}
