package com.led.led;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.support.v7.internal.widget.AdapterViewCompat;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;
import java.io.IOException;
import java.lang.String;
import java.util.UUID;


public class ledControl extends ActionBarActivity { //implements AdapterView.OnItemSelectedListener{

    Button btnOn, btnOff, btnDis, btnS1, btnS2, btnS3, btnS4, btnS5, btnS6;
    SeekBar brightness, red, green, blue,ringnumber;
    TextView lumn, lumnred,lumngreen,lumnblue,l,r,g,b;
    ImageButton c1,c2,c3,c4,c5,c6,c7;

    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket Socket = null;
    private boolean isBtConnected = false;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device

        //view of the ledControl
        setContentView(R.layout.activity_led_control);

        //call the widgtes
        btnOff = (Button)findViewById(R.id.button3);
        btnDis = (Button)findViewById(R.id.button4);
        btnS1 = (Button)findViewById(R.id.button5);
        btnS2 = (Button)findViewById(R.id.button6);
        btnS3 = (Button)findViewById(R.id.button7);
        btnS4 = (Button)findViewById(R.id.button8);
        btnS5 = (Button)findViewById(R.id.button9);
        btnS6 = (Button)findViewById(R.id.button10);
        brightness = (SeekBar)findViewById(R.id.seekBar);
        lumn = (TextView)findViewById(R.id.lumn);
        red = (SeekBar)findViewById(R.id.seekBar2);
        green = (SeekBar)findViewById(R.id.seekBar3);
        blue = (SeekBar)findViewById(R.id.seekBar4);
        lumnred = (TextView)findViewById(R.id.lumn_red);
        lumngreen = (TextView)findViewById(R.id.lumn_green);
        lumnblue = (TextView)findViewById(R.id.lumn_blue);
        l = (TextView)findViewById(R.id.l);
        r = (TextView)findViewById(R.id.r);
        g = (TextView)findViewById(R.id.g);
        b = (TextView)findViewById(R.id.b);
        c1 = (ImageButton)findViewById(R.id.imageButton2);
        c2 = (ImageButton)findViewById(R.id.imageButton3);
        c3 = (ImageButton)findViewById(R.id.imageButton4);
        c4 = (ImageButton)findViewById(R.id.imageButton5);
        c5 = (ImageButton)findViewById(R.id.imageButton6);
        c6 = (ImageButton)findViewById(R.id.imageButton7);
        c7 = (ImageButton)findViewById(R.id.imageButton8);
        ringnumber = (SeekBar)findViewById(R.id.seekBar5);


        new ConnectBT().execute(); //Call the class to connect

        //commands to be sent to bluetooth

        btnOff.setOnClickListener(new OnClickListener() {  //Turn off - Button
            @Override
            public void onClick(View v)
            {
                turnOffLed();
            }
        });

        btnS1.setOnClickListener(new OnClickListener(){  //Sequence1 - button
        public void onClick(View v)
        {
            if (Socket!=null)
            {
                try
                {
                    Socket.getOutputStream().write('a');
                }
                catch (IOException e)
                {
                    msg("Error");
                }
            }
        }
        });

        btnS2.setOnClickListener(new OnClickListener(){  //Sequence2 - button
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('b');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnS3.setOnClickListener(new OnClickListener(){  //Sequence3 - button
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('c');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnS4.setOnClickListener(new OnClickListener(){  //Sequence4 - button
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('d');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnS5.setOnClickListener(new OnClickListener(){  //Sequence5 - button
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('e');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnS6.setOnClickListener(new OnClickListener(){  //Sequence6 - button
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('f');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        btnDis.setOnClickListener(new OnClickListener()  //Disconnected - button (return to the first layout PairDev)
        {
            @Override
            public void onClick(View v)
            {
                Disconnect();
            }
        });



        brightness.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() { //brightness - button
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumn.setText(String.valueOf(progress));
                    Integer pr=progress*10;
                    l.setText(String.valueOf(pr)+ "%");

                    try
                    {
                        Socket.getOutputStream().write('L'); //+Integer.valueOf(progress));

                        Socket.getOutputStream().write(Integer.valueOf(progress));

                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });


        red.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {  //red-seekbar - button
            @Override
            public void onProgressChanged(SeekBar seekBar2, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumnred.setText(String.valueOf(progress));
                    Integer pr=progress*4-1;
                    if(pr==-1)
                    {
                        pr=pr+1;
                    }
                    r.setText(String.valueOf(pr));
                    try
                    {
                        // String Str2 = new String (Str1.getBytes( "UTF-8" ));
                        // Socket.getOutputStream().write(Str2.getBytes());
                        Socket.getOutputStream().write('R');
                        Socket.getOutputStream().write(Integer.valueOf(progress));
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        green.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {  //green-seekbar - button
            @Override
            public void onProgressChanged(SeekBar seekBar3, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumngreen.setText(String.valueOf(progress));
                    Integer pr=progress*4-1;
                    if(pr==-1)
                    {
                        pr=pr+1;
                    }
                    g.setText(String.valueOf(pr));
                    try
                    {
                        Socket.getOutputStream().write('G');
                        Socket.getOutputStream().write(Integer.valueOf(progress));
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        blue.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {   //blue-seekbar - button
            @Override
            public void onProgressChanged(SeekBar seekBar4, int progress, boolean fromUser) {
                if (fromUser==true)
                {
                    lumnblue.setText(String.valueOf(progress));
                    Integer pr=progress*4-1;
                    if(pr==-1)
                    {
                        pr=pr+1;
                    }
                    b.setText(String.valueOf(pr));
                    try
                    {
                        Socket.getOutputStream().write('B');
                        Socket.getOutputStream().write(Integer.valueOf(progress));
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }

            }
            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }
            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        c1.setOnClickListener(new OnClickListener(){  //color1
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('g');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });
        c2.setOnClickListener(new OnClickListener(){  //color2
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('h');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        c3.setOnClickListener(new OnClickListener(){  //color3
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('i');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        c4.setOnClickListener(new OnClickListener(){  //color4
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('j');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        c5.setOnClickListener(new OnClickListener(){  //color5
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('k');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        c6.setOnClickListener(new OnClickListener(){  //color6
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('l');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }
        });

        c7.setOnClickListener(new OnClickListener(){  //color7
            public void onClick(View v)
            {
                if (Socket!=null)
                {
                    try
                    {
                        Socket.getOutputStream().write('m');
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
                }
            }

        });

        ringnumber.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){  //SELECT RING NUMBER - default Ring1

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

                if (fromUser==true)
                {
                    if(progress==0)

                        try
                        {
                            Socket.getOutputStream().write('x');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    if(progress==1)
                    {
                        try
                        {
                            Socket.getOutputStream().write('y');
                        }
                        catch (IOException e)
                        {
                            msg("Error");
                        }
                    }
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

    }


    //SPINNER
   // @Override
    //public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {

   //     TextView myText= (TextView) view;
   //     Toast.makeText(this,"You Selceted "+myText.getText(),Toast.LENGTH_SHORT).show();


   // }

   // @Override
    //public void onNothingSelected(AdapterView<?> parent) {

   // }

    private void Disconnect()
    {
        if (Socket!=null) //If the btSocket is busy
        {
            try
            {
                Socket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout(paired)

    }

    private void turnOffLed()  //Procedure TurnOff
    {
        if (Socket!=null)
            {
                try
                {
                    red.setProgress(0);
                    green.setProgress(0);
                    blue.setProgress(0);
                    changevar();
                    Socket.getOutputStream().write('O');

                }
                catch (IOException e)
                {
                    msg("Error");
                }
        }
    }
    public void changevar()  //WYRESETOWANIE WSZYSTKICH WARTOSCI- USATWIENIE SEEKBARÓW NA wart. pocz.
    {
                    Integer pr=0;
                    lumnred.setText(String.valueOf(progress));
                    r.setText(String.valueOf(pr));
                    lumngreen.setText(String.valueOf(progress));
                    g.setText(String.valueOf(pr));
                    lumnblue.setText(String.valueOf(progress));
                    b.setText(String.valueOf(pr));

                    try
                    {
                        Socket.getOutputStream().write('R');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                        Socket.getOutputStream().write('G');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                        Socket.getOutputStream().write('B');
                        Socket.getOutputStream().write(Integer.valueOf(pr));
                    }
                    catch (IOException e)
                    {
                        msg("Error");
                    }
    }

    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }




    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (Socket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                 Socket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 Socket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed");
                finish();
            }
            else
            {
                msg("Connected");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}
