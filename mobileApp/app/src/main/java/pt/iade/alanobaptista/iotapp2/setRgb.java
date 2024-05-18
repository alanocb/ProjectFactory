package pt.iade.alanobaptista.iotapp2;

import android.os.AsyncTask;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;

public class setRgb extends AsyncTask<Void, Void, Void> {

    private static final String API_URL = "http://10.0.2.2:3000/rgb";
    private int red;
    private int green;
    private int blue;

    public setRgb(int red, int green, int blue) {
        this.red = red;
        this.green = green;
        this.blue = blue;
    }

    @Override
    protected Void doInBackground(Void... voids) {
        try {
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("r", red);
            jsonObject.put("g", green);
            jsonObject.put("b", blue);
            String jsonData = jsonObject.toString();
            RequestBody requestBody = RequestBody.create(jsonData, MediaType.parse("application/json; charset=utf-8"));

            OkHttpClient client = new OkHttpClient();

            Request request = new Request.Builder()
                    .url(API_URL)
                    .post(requestBody)
                    .build();

            Response response = client.newCall(request).execute();

            if (response.isSuccessful()) {
                ResponseBody responseBody = response.body();
                if (responseBody != null) {
                    String responseString = responseBody.string();
                    System.out.println(responseString);
                }
            } else {
                System.err.println("Request failed: " + response.message());
            }
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    protected void onPostExecute(Void aVoid) {
        super.onPostExecute(aVoid);
    }
}
