package blogsdpteamg.mobilecameracontrol;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Looper;
import android.os.Message;
import android.preference.PreferenceFragment;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.app.ActionBar;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.support.v4.widget.DrawerLayout;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.math.BigInteger;
import java.util.Queue;
import java.util.UUID;
import java.util.logging.Handler;
import java.util.logging.LogRecord;

import blogsdpteamg.mobilecameracontrol.Connecting.ServerConnectThread;
import blogsdpteamg.mobilecameracontrol.MainScreenFragment;


public class MainActivity extends AppCompatActivity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks,
        DeviceListFragment.OnFragmentInteractionListener,
        MainScreenFragment.OnFragmentInteractionListener{

    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;

    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;

    /**
     * Bluetooth Stuff
     */
    private DeviceListFragment mDeviceListFragment;
    private BluetoothAdapter BTAdapter;
    private BluetoothSocket BTSocket;
    private BluetoothDevice device;
    private UUID mUUID;
    private ConnectThread connection;
    private Queue<String> packets;
    public static int MESSAGE_READ = 2;

    /**
     * Servo Angles and degree steps
     */
    private float pitch;
    private float yaw;
    private float pitchStep;
    private float yawStep;

    /**
     * Message Handler
     */
    //private static Handler mHandler;


    public static int REQUEST_BLUETOOTH = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getSupportFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));

        // Setup Bluetooth
        connection = null;
        BTAdapter = BluetoothAdapter.getDefaultAdapter();
        String temp = getString(R.string.uuid);
        String temp2 = temp.replace("-", "");
        mUUID = new UUID(
                new BigInteger(temp2.substring(0,16),16).longValue(),
                new BigInteger(temp2.substring(16),16).longValue()
        );

        if(!BTAdapter.isEnabled())
        {
            Intent enableBT = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBT, REQUEST_BLUETOOTH);
        }

        // Setup Servo controls
        pitch = (float) 65.0;
        yaw = (float) 85.0;
        pitchStep = (float) 2.5;
        yawStep = (float) 2.5;
    }


    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getSupportFragmentManager();
        if(position == 2) {
            fragmentManager.beginTransaction()
                    .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
                    .commit();
        }
        else if(position == 0)
        {
            fragmentManager.beginTransaction()
                    .replace(R.id.container, MainScreenFragment.newInstance(position + 1))
                    .commit();
        }
        else
        {
            if(mDeviceListFragment == null)
            {
                mDeviceListFragment = DeviceListFragment.newInstance(BTAdapter,position + 1);
            }
            fragmentManager.beginTransaction()
                    .replace(R.id.container, mDeviceListFragment)
                    .commit();
        }
    }

    public void onSectionAttached(int number) {
        switch (number) {
            case 1:
                mTitle = getString(R.string.title_section1);
                getSupportActionBar().hide();
                break;
            case 2:
                mTitle = getString(R.string.title_section2);
                getSupportActionBar().show();
                break;
            case 3:
                mTitle = getString(R.string.title_section3);
                getSupportActionBar().show();
                break;
        }
    }

    public void restoreActionBar() {
        ActionBar actionBar = getSupportActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setTitle(mTitle);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!mNavigationDrawerFragment.isDrawerOpen()) {
            // Only show items in the action bar relevant to this screen
            // if the drawer is not showing. Otherwise, let the drawer
            // decide what to show in the action bar.
            getMenuInflater().inflate(R.menu.main, menu);
            restoreActionBar();
            return true;
        }
        return super.onCreateOptionsMenu(menu);
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

    /**
     * Bluetooth Fragment Interface Functions
     */
    @Override
    public void onFragmentInteraction(String id)
    {
        device = BTAdapter.getRemoteDevice(id);

        connection = new ConnectThread(device,mUUID);
        connection.connect();
    }

    @Override
    public BluetoothAdapter updateBluetooth()
    {
        return BTAdapter;
    }

    /**
     * Main Screen Interface Functions
     */
    @Override
    public void onButtonClick(String id)
    {
        if(connection != null) {

            if (connection.isConnected()) {
                // Format Packet
                String packet = "$";

                switch (id) {
                    case "UP":
                        float newPitchUp = pitch + pitchStep;
                        packet += "%PWM%PITCH" + String.valueOf(newPitchUp) + "%YAW" + String.valueOf(yaw) + "$";
                        Log.d("Bluetooth", "Sending packet[" + packet + "]\n");
                        connection.write(packet.getBytes());
                        break;
                    case "DOWN":
                        float newPitchDown = pitch - pitchStep;
                        packet += "%PWM%PITCH" + String.valueOf(newPitchDown) + "%YAW" + String.valueOf(yaw) + "$";
                        Log.d("Bluetooth", "Sending packet[" + packet + "]\n");
                        connection.write(packet.getBytes());
                        break;
                    case "LEFT":
                        float newYawLeft = yaw - yawStep;
                        packet += "%PWM%PITCH" + String.valueOf(pitch) + "%YAW" + String.valueOf(newYawLeft) + "$";
                        Log.d("Bluetooth", "Sending packet[" + packet + "]\n");
                        connection.write(packet.getBytes());
                        break;
                    case "RIGHT":
                        float newYawRight = yaw + yawStep;
                        packet += "%PWM%PITCH" + String.valueOf(pitch) + "%YAW" + String.valueOf(newYawRight) + "$";
                        Log.d("Bluetooth", "Sending packet[" + packet + "]\n");
                        connection.write(packet.getBytes());
                        break;
                    case "CAPTURE":
                        packet += "%CAMERA%DOWNLOAD" + String.valueOf(false) + "$";
                        Log.d("Bluetooth", "Sending packet[" + packet + "]\n");
                        connection.write(packet.getBytes());
                        break;
                    default:
                        // Should not have this
                        break;
                }
            }
        }
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        private static final String ARG_SECTION_NUMBER = "section_number";

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        public PlaceholderFragment() {
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_placeholder, container, false);
            return rootView;
        }

        @Override
        public void onAttach(Activity activity) {
            super.onAttach(activity);
            ((MainActivity) activity).onSectionAttached(
                    getArguments().getInt(ARG_SECTION_NUMBER));
        }
    }

}
