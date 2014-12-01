using System;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;

namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {
        string host = "http://68.14.247.232";
        Button[] playButton;

        public Form1()
        {
            InitializeComponent();
            StartGameMenu.Visible = false;
            playButton = new Button[] { play1, play2, play3, play4, play5, play6, play7, play8, play9 };
        }

        public string getData(string sURL)
        {
            WebRequest wrGETURL;
            wrGETURL = WebRequest.Create(sURL);
            Stream objStream;
            objStream = wrGETURL.GetResponse().GetResponseStream();
            StreamReader objReader = new StreamReader(objStream);
            string ret = objReader.ReadToEnd();
            return ret;
        }


        public void runGame(int player, string secret, int turn, int[] board)
        {
            if (turn == player)
            {
                whatTurn.Text = "Your Turn";
            }
            else
            {
                whatTurn.Text = "Waiting for other player";
            }
            for (int i = 0; i < board.Length; i++)
            {
                if (board[i] == 1)
                {
                    playButton[i].Visible = false;
                }
                else if (board[i] == 2)
                {

                }
            }
        }

        public bool validPin(string pin)
        {
            if (pin.Length != 4)
            {
                return false;
            }
            for (int i = 0; i < pin.Length; i++)
            {
                if (pin[i] < '0' || pin[i] > '9')
                {
                    return false;
                }
            }
            return true;
        }

        public string remspace(string x)
        {
            string ret = "";
            for (int i = 0; i < x.Length; i++)
            {
                if (x[i] == ' ') {
                    ret = ret + '+';
                } else {
                    ret = ret + x[i];
                }
            }
            return ret;
        }

        private void startGame(object sender, EventArgs e)
        {
            MainMenu.Visible = false;
            StartGameMenu.Visible = true;
        }

        private void GetStarted_Click(object sender, EventArgs e)
        {
            string name = yourName.Text;
            int letter = 1;
            if (pickO.Checked)
            {
                letter = 2;
            }
            string description = Description.Text;
            int priv = 0;
            if (pickYes.Checked)
            {
                priv = 1;
            }
            string pin = pinBox.Text;
            if (name == "")
            {
                GetStarted.Text = "No name entered!";
                return;
            }
            if (priv == 1)
            {
                if (validPin(pin) == false)
                {
                    GetStarted.Text = "Invalid pin!";
                    return;
                }
            }
            if (priv == 0) {
                string response = getData(host + "/startGame?name=" + remspace(name) + "&description=" + remspace(description) + "&letter=" + letter.ToString() + "&private=0");
                JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                if (jsonResponse.status == "error")
                {
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1, MessageBoxOptions.RightAlign, true);
                    return;
                }
                StartGameMenu.Visible = false;
                playGame.Visible = true;
                int[] nboard = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                runGame(jsonResponse.letter, jsonResponse.secret, 1, nboard);
            } else {
                string response = getData(host + "/startGame?name=" + remspace(name) + "&description=" + remspace(description) + "&letter=" + letter.ToString() + "&private=1&pin=" + pin.ToString());
                JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                if (jsonResponse.status == "error")
                {
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning, MessageBoxDefaultButton.Button1, MessageBoxOptions.RightAlign, true);
                    return;
                }
                StartGameMenu.Visible = false;
                playGame.Visible = true;
                int[] nboard = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                runGame(jsonResponse.letter, jsonResponse.secret, 1, nboard);
            }
        }

        private void GoBack_Click(object sender, EventArgs e)
        {
            StartGameMenu.Visible = false;
            MainMenu.Visible = true;
        }

        private void pickX_CheckedChanged(object sender, EventArgs e)
        {
            if (pickX.Checked)
            {
                pickO.Checked = false;
            }
        }

        private void pickO_CheckedChanged(object sender, EventArgs e)
        {
            if (pickO.Checked)
            {
                pickX.Checked = false;
            }
        }

        private void pickYes_CheckedChanged(object sender, EventArgs e)
        {
            if (pickYes.Checked)
            {
                pickNo.Checked = false;
            }
        }

        private void pickNo_CheckedChanged(object sender, EventArgs e)
        {
            if (pickNo.Checked)
            {
                pickYes.Checked = false;
            }
        }

    }

    class JsonProcess
    {
        public string status = "";
        public string secret = "";
        public int code = 0;
        public string message = "";
        public string id = "";
        public int letter = 0;
        public int[] board = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        public int turn = 0;
        public int winner = 0;
    }
}
