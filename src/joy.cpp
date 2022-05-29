#include "joy.h"

using namespace std;

void JoyInput::feed(sensor_msgs::JoyConstPtr msg)
{
    joy_msg = *msg;
    joy_data_recived_flag = 1;
}
int Joy::calulateRC(int channel, int reverse)
{
    int output;
    if (channel <= 6)
    {
        // cout << "joyinput.joy_msg.axes[channel]:" << joyinput.joy_msg.axes[channel] << endl;
        output = remapRC(joyinput.joy_msg.axes[channel], reverse);
    }
    else
    {
        output = remapRC(joyinput.joy_msg.buttons[channel - 7], reverse);
    }
    // cout << "output:" << output << endl;
    return output;
}
int Joy::remapRC(double input, int reverse)
{
    int res;
    res = (input + 1.0) * 500.0 + 1000.0;
    if (reverse)
    {

        res = 3000 - res;
    }
    // cout << "res:" << res << endl;
    return res;
}

void Joy::pubRC()
{
    if (joyinput.joy_data_recived_flag)
    {
        mavros_msgs::RCIn rc_msg;
        rc_msg.header.stamp = ros::Time::now();
        int channel_size = joy_RC_joy_channel.size();
        // cout << "channel_size:" << channel_size << endl;
        rc_msg.channels.reserve(channel_size);
        for (auto i = 0; i < channel_size; i++)
        {
            // cout << "joy_RC_joy_channel[i]:" << joy_RC_joy_channel[i] << endl;
            // cout << "joy_RC_joy_reverse[i]:" << joy_RC_joy_reverse[i] << endl;
            rc_msg.channels.push_back(calulateRC(joy_RC_joy_channel[i], joy_RC_joy_reverse[i]));
        }
        joyRC_pub.publish(rc_msg);
    }
}
void Joy::config_from_ros_handle(const ros::NodeHandle &nh)
{
    read_essential_param(nh, "joy_freq_max", joy_freq_max);
    read_essential_param(nh, "joy_channel_num", joy_channel_num);
    for (auto i = 0; i < joy_channel_num; i++)
    {
        int tmp_channel;
        read_essential_param(nh, "joy_RC" + to_string(i) + "_joy_channel", tmp_channel);

        int tmp_reverse;
        read_essential_param(nh, "joy_RC" + to_string(i) + "_joy_reverse", tmp_reverse);
        cout << "tmp_channel:" << tmp_channel << endl;
        cout << "tmp_reverse:" << tmp_reverse << endl;
        joy_RC_joy_channel.push_back(tmp_channel);
        joy_RC_joy_reverse.push_back(tmp_reverse);
    }
}
