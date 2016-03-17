package blogsdpteamg.mobilecameracontrol;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class ConnectThread extends Thread{

    private final BluetoothDevice bTDevice;
    private final BluetoothSocket bTSocket;
    private final InputStream inputStream;
    private final OutputStream outputStream;
    private final Handler mHandler;

    private int MESSAGE_READ = 2;

    public ConnectThread(BluetoothDevice bTDevice, UUID UUID, Handler m_Handler) {
        // First Create Socket and null the streams
        BluetoothSocket tmp = null;
        InputStream tempIn = null;
        OutputStream tempOut = null;
        mHandler = m_Handler;
        this.bTDevice = bTDevice;

        try {
            tmp = this.bTDevice.createRfcommSocketToServiceRecord(UUID);
        }
        catch (IOException e) {
            Log.d("CONNECTTHREAD", "Could not start listening for RFCOMM");
        }
        bTSocket = tmp;

        // Now Make the streams
        try {
            tempIn = bTSocket.getInputStream();
            tempOut = bTSocket.getOutputStream();
        }
        catch(IOException e)
        {

        }

        inputStream = tempIn;
        outputStream = tempOut;
    }

    public boolean connect() {

        try {
            bTSocket.connect();
        } catch(IOException e) {
            Log.d("CONNECTTHREAD","Could not connect: " + e.toString());
            try {
                bTSocket.close();
            } catch(IOException close) {
                Log.d("CONNECTTHREAD", "Could not close connection:" + e.toString());
                return false;
            }
        }
        return true;
    }

    public boolean cancel() {
        try {
            bTSocket.close();
        } catch(IOException e) {
            return false;
        }
        return true;
    }

    public void run()
    {
        byte[] buffer = new byte[1024];
        int bytes;

        // Listen to Input stream until we hit an exception
        while(true)
        {
            try
            {
                // Read bytes
                bytes = inputStream.read(buffer);
                // Send bytes to main activity
                String temp = new String(buffer);
                Log.d("Thread","Received: ["+temp+"]");
                mHandler.obtainMessage(MESSAGE_READ,bytes,-1,buffer)
                .sendToTarget();
            }
            catch (IOException e)
            {
                break;
            }
        }
    }

    public void write(byte[] bytes)
    {
        try
        {
            outputStream.write(bytes);
        }
        catch (IOException e)
        {

        }
    }

    public boolean isConnected()
    {
        return bTSocket.isConnected();
    }

}