package com.example.danyal.bluetoothhc05;

import android.annotation.SuppressLint;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.UUID;

import io.github.controlwear.virtual.joystick.android.JoystickView;

public class ledControl extends AppCompatActivity {

    Button btn,btn1, btn2, btn3, btn4, btn5, btnDis;
    String address = null;
    TextView lumn;
    byte start_pos,line;

    char dir;

    String message = "";
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS);

        setContentView(R.layout.activity_led_control);

        btn = (Button) findViewById(R.id.button8);
        btn5 = (Button) findViewById(R.id.button7);
        btnDis = (Button) findViewById(R.id.button4);
        lumn = (TextView) findViewById(R.id.textView2);

        JoystickView joystickLeft = (JoystickView) findViewById(R.id.joystickView);


        joystickLeft.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                if (strength > 50) {
                    // String message = Integer.toString(angle) +" "+ Sstrength+"/n";
                    if(0<angle && angle <45|| 315<angle && angle<360){
                        dir = 'r';
                        sendSignal(Byte.toString(start_pos)+ dir + Byte.toString(line));
                    }

                    if(45<angle && angle <135){
                        dir = 'f';
                        sendSignal(Byte.toString(start_pos)+ dir + Byte.toString(line));
                    }


                    if(135<angle && angle<225){
                        dir = 'l';
                        sendSignal(Byte.toString(start_pos)+ dir + Byte.toString(line));
                    }


                    if(225<angle && angle<315){
                        dir = 'b';
                        sendSignal(Byte.toString(start_pos)+ dir + Byte.toString(line));
                    }

                }
            }
        });

        new ConnectBT().execute();
        new ReadBT().execute();

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick (View v) {
                if(start_pos != 1) {
                    start_pos = 1;
                    dir = 'n';
                    btn.setText("Start");
                    sendSignal(Byte.toString(start_pos)+ dir + Byte.toString(line));
                }
                else{
                    btn.setText("Stop");

                    start_pos = 0;
                }
            }
        });


        btn5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick (View v) {
                if(start_pos==1 && line != 1){
                    line = 1;
                    dir = 'n';
                    btn5.setText("Line follow on");
                    sendSignal(Byte.toString(start_pos)+  dir + Byte.toString(line));
                }
                else{
                    line = 0;
                    dir = 'n';
                    btn5.setText("Line follow off");
                    sendSignal(Byte.toString(start_pos)+  dir + Byte.toString(line));
                    msg ("Locked, press start to start");
                }
            }
        });

        btnDis.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick (View v) {
                Disconnect();
            }
        });
    }


    private void sendSignal ( String number ) {
        if ( btSocket != null ) {
            try {
                btSocket.getOutputStream().write(number.toString().getBytes());
            } catch (IOException e) {
                msg("Error");
            }
        }
    }

    private void Disconnect () {
        if ( btSocket!=null ) {
            try {
                btSocket.close();
            } catch(IOException e) {
                msg("Error");
            }
        }

        finish();
    }

    private void msg (String s) {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_LONG).show();
    }

    private class ConnectBT extends AsyncTask<Void, String, Void> {
        private boolean ConnectSuccess = true;

        @Override
        protected  void onPreExecute () {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please Wait!!!");
        }


        @Override
        protected Void doInBackground (Void... devices) {
            try {
                if ( btSocket==null || !isBtConnected ) {
                    myBluetooth = BluetoothAdapter.getDefaultAdapter();
                    BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);
                    btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    btSocket.connect();
                }
            } catch (IOException e) {
                ConnectSuccess = false;
            }
            return null;
        }

            @Override
        protected void onPostExecute (Void result) {
            super.onPostExecute(result);
            if (!ConnectSuccess) {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            } else {
                msg("Connected");
                isBtConnected = true;
            }

            progress.dismiss();
        }
    }

    private class ReadBT extends AsyncTask<Void, String, Void> {

        @Override
        protected  void onPreExecute () {

        }


        @Override
        protected Void doInBackground (Void... devices) {
            try {
                if ( btSocket!=null || isBtConnected ) {
                    BufferedInputStream in = new BufferedInputStream(btSocket.getInputStream());
                    byte[] contents = new byte[1024];

                    int bytesRead = 0;
                    while((bytesRead = in.read(contents)) != -1) {
                        if(message.length() < 100) {
                            message += new String(contents, 0, bytesRead);
                            publishProgress(message);
                        }
                        else{
                            message = "";
                        }
                    }

                }
            } catch (IOException e) {

            }

            return null;
        }

        protected void onProgressUpdate(String... values) {
            lumn.setText(values[0]);
        }
        @Override
        protected void onPostExecute (Void result) {
            super.onPostExecute(result);

        }
    }

}
