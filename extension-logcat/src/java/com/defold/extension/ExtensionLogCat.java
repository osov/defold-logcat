package com.defold.extension;

import android.util.Log;
import android.app.Activity;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONException;


public class ExtensionLogCat {

  private static String TAG = "ExtensionLogCat";
  public static native void AddToQueue(int msg, String json);
  private static final int MSG_TYPE_NONE = 1;
  private static final int EVENT_JSON_ERROR = 101;
  private Activity activity;


  public ExtensionLogCat(Activity mainActivity) {
    activity = mainActivity;
  }

  public void initialize(final String key) {
    activity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        Log.d(TAG, "initialize");
        TAG = key;
        sendSimpleMessage(MSG_TYPE_NONE, "init", key);
      }
    });
  }

  public void ReportEvent(final String msg, final String event) {
  	activity.runOnUiThread(new Runnable() {
      @Override
      public void run() {
        if (event.equals("e"))
          Log.e(TAG, msg);
        else if (event.equals("w"))
          Log.w(TAG, msg);
        else 
          Log.d(TAG, msg);
      }
    });
  }


  private String getJsonConversionErrorMessage(String messageText) {
    String message = null;
    try {
      JSONObject obj = new JSONObject();
      obj.put("error", messageText);
      obj.put("event", EVENT_JSON_ERROR);
      message = obj.toString();
    } catch (JSONException e) {
      message = "{ \"error\": \"Error while converting simple message to JSON.\", \"event\": " + EVENT_JSON_ERROR
          + " }";
    }
    return message;
  }


  private void sendSimpleMessage(int msg, String key, String value) {
    String message = null;
    try {
      JSONObject obj = new JSONObject();
      obj.put(key, value);
      message = obj.toString();
    } catch (JSONException e) {
      message = getJsonConversionErrorMessage(e.getLocalizedMessage());
    }
    AddToQueue(msg, message);
  }


}
