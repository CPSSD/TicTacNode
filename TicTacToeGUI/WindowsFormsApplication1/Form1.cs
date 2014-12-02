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
using System.Threading;
using Newtonsoft.Json;
using System.Diagnostics;

namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {
        string host = "http://68.14.247.232";
        bool myTurn = false;
        int doMove = -1;
        Button[] playButton;
        Label[] xs;
        Label[] os;

        //Data for the gamesList
        int currentpage;
        gameObject[] prevgames;
        Label[] ids;
        Label[] gameby;
        Label[] descs;
        Label[] playas;
        Label[] pubs;
        TextBox[] pins;
        GroupBox[] groupB;

        public Form1()
        {
            InitializeComponent();
            StartGameMenu.Visible = false;
            playButton = new Button[] { play1, play2, play3, play4, play5, play6, play7, play8, play9 };
            xs = new Label[] { x1, x2, x3, x4, x5, x6, x7, x8, x9 };
            os = new Label[] { o1, o2, o3, o4, o5, o6, o7, o8, o9 };
            ids = new Label[] { gameId1, gameId2, gameId3, gameId4};
            gameby = new Label[] { startedBy1, startedBy2, startedBy3, startedBy4};
            descs = new Label[] { description1, description2, description3, description4};
            playas = new Label[] { playAs1, playAs2, playAs3, playAs4};
            pubs = new Label[] { public1, public2, public3, public4};
            pins = new TextBox[] { pin1, pin2, pin3, pin4};
            groupB = new GroupBox[] { groupBox1, groupBox2, groupBox3, groupBox4};
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

        public int oppsiteTurn(int turn)
        {
            if (turn == 1)
            {
                return 2;
            }
            return 1;
        }

        public int getWinner(int[] board)
        {
            for (int i = 0; i < 3; i++)
            {
                if (board[i * 3] == board[i * 3 + 1] && board[i*3] == board[i * 3 + 1] && board[i*3] != 0)
                {
                    return board[i * 3];
                }
                if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != 0)
                {
                    return board[i];
                }
            }
            if (board[0] == board[4] && board[0] == board[8] && board[0] != 0)
            {
                return board[0];
            }
            if (board[2] == board[4] && board[2] == board[6] && board[2] != 0)
            {
                return board[2];
            }
            for (int i = 0; i < 9; i++)
            {
                if (board[i] == 0)
                {
                    return -1;
                }
            }
            return 0;
        }

        public void showBoard(int turn, int player, int[] board)
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
                    xs[i].Visible = true;
                    os[i].Visible = false;
                }
                else if (board[i] == 2)
                {
                    playButton[i].Visible = false;
                    xs[i].Visible = false;
                    os[i].Visible = true;
                }
                else
                {
                    playButton[i].Visible = true;
                    xs[i].Visible = false;
                    os[i].Visible = false;
                }
            }
        }

        public void runGame(int player, string secret, int turn, int[] board)
        {
            doMove = -1;
            showBoard(turn, player, board);
            int count = 0;
            if (player == turn)
            {
                myTurn = true;
            }
            else
            {
                myTurn = false;
            }
            while (true)
            {
                count++;
                if (player == turn)
                {
                    if (doMove == -2)
                    {
                        MainMenu.Visible = true;
                        playGame.Visible = false;
                        if (getWinner(board) == -1)
                        {
                            getData(host + "/endGame?secret=" + secret);
                        }
                        return;
                    }
                    else if (doMove != -1)
                    {
                        myTurn = false;
                        board[doMove] = player;
                        turn = oppsiteTurn(turn);
                        showBoard(turn, player, board);
                        string response = getData(host + "/move?secret=" + secret + "&position=" + doMove.ToString());
                        JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                        if (jsonResponse.status == "error")
                        {
                            MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                            playGame.Visible = false;
                            MainMenu.Visible = true;
                            return;
                        }
                        if (getWinner(board) >= 0)
                        {
                            if (getWinner(board) == 0)
                            {
                                whatTurn.Text = "Game Drawn!";
                            }
                            else if (getWinner(board) == player)
                            {
                                whatTurn.Text = "You have won, well done";
                            }
                            else
                            {
                                whatTurn.Text = "You have lost the game";
                            }
                        }
                        doMove = -1;
                    }
                    else
                    {
                        Application.DoEvents();
                        Thread.Sleep(10);
                    }
                }
                else
                {
                    if (doMove == -2)
                    {
                        MainMenu.Visible = true;
                        playGame.Visible = false;
                        getData(host + "/endGame?secret=" + secret);
                        return;
                    }
                    if (count >= 100)
                    {
                        count = 0;
                        string response = getData(host + "/next?secret=" + secret);
                        JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                        if (jsonResponse.status == "error")
                        {
                            MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                        }
                        else
                        {
                            if (jsonResponse.winner >= 0)
                            {
                                board = jsonResponse.board;
                                showBoard(turn, player, board);
                                if (jsonResponse.winner == 0)
                                {
                                    whatTurn.Text = "Game Drawn!";
                                }
                                else if (jsonResponse.winner == player)
                                {
                                    whatTurn.Text = "You have won, well done";
                                }
                                else
                                {
                                    whatTurn.Text = "You have lost the game";
                                }
                            }
                            if (jsonResponse.turn == player)
                            {
                                turn = player;
                                myTurn = true;
                                board = jsonResponse.board;
                                showBoard(turn, player, board);
                            }
                        }
                    }
                    Application.DoEvents();
                    Thread.Sleep(10);
                }
            }
        }

        public void makeMove(object sender, EventArgs e)
        {
            string name = ((Button)sender).Name;
            int num = name.Last() - '0';
            if (myTurn)
            {
                doMove = num - 1;
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
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
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
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
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

        private void ExitGame_Click(object sender, EventArgs e)
        {
            doMove = -2;
        }

        private void Exit_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Settings_Click(object sender, EventArgs e)
        {
            MainMenu.Visible = false;
            showSettings.Visible = true;
            curHost.Text = "Current : " + host;
            enterBelow.Text = "Enter new host below : ";
        }

        private void noChange_Click(object sender, EventArgs e)
        {
            showSettings.Visible = false;
            MainMenu.Visible = true;
        }

        public bool goodHost(string x)
        {
            if (x.Substring(0, 7) != "http://")
            {
                return false;
            }
            string response = getData(x + "/version");
            JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
            if (jsonResponse.status != "okay")
            {
                return false;
            }
            return true;
        }

        private void Change_Click(object sender, EventArgs e)
        {
            if (goodHost(selectHost.Text) == false)
            {
                enterBelow.Text = "Invalid host entered!";
            }
            else
            {
                host = selectHost.Text;
                curHost.Text = "Current : " + host;
            }
        }

        private gameObject[] getGames(string response)
        {
            List<gameObject> list = new List<gameObject>();
            dynamic process = JsonConvert.DeserializeObject(response);
            foreach (var s in process.games)
            {
                gameObject x = new gameObject();
                x.id = s.id;
                x.description = s.description;
                x.name = s.name;
                x.letter = s.letter;
                x.privat = s.@private;
                list.Add(x);
            }
            gameObject[] ret = list.ToArray();
            return ret;
        }

        private void getPage(int pagen, gameObject[] games)
        {
            currentpage = pagen;
            if (pagen > 1)
            {
                lastPage.Visible = true;
            }
            else
            {
                lastPage.Visible = false;
            }
            int maxpage = (games.Length + 3) / 4;
            if (pagen < maxpage)
            {
                nextPage.Visible = true;
            }
            else
            {
                nextPage.Visible = false;
            }
            page.Text = "Page " + pagen.ToString() + "/" + maxpage.ToString();
            int first = (pagen - 1) * 4;
            for (int i = 0; i < 4; i++)
            {
                if (first + i < games.Length)
                {
                    groupB[i].Visible = true;
                    ids[i].Text = "Game Id : " + games[first + i].id;
                    gameby[i].Text = "Started by " + games[first + i].name;
                    descs[i].Text = games[first + i].description;
                    if (games[first + i].letter == 1) {
                        playas[i].Text = "Play as X";
                    }
                    else
                    {
                        playas[i].Text = "Play as O";
                    }
                    if (games[first + i].privat == 1)
                    {
                        pubs[i].Visible = false;
                        pins[i].Visible = true;
                        pins[i].Text = "Enter pin here";
                    }
                    else
                    {
                        pubs[i].Visible = true;
                        pins[i].Visible = false;
                    }
                }
                else
                {
                    groupB[i].Visible = false;
                }
            }
        }

        private void JoinGame_Click(object sender, EventArgs e)
        {
            gamesList.Visible = true;
            string response = getData(host + "/listGames");
            JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
            if (jsonResponse.status == "okay")
            {
                gameObject[] games = getGames(response);
                prevgames = games;
                getPage(1, games);
            }
            else
            {
                MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                MainMenu.Visible = true;
                gamesList.Visible = false;
            }
            Application.DoEvents();
            MainMenu.Visible = false;
        }

        private void lastPage_Click(object sender, EventArgs e)
        {
            getPage(currentpage - 1, prevgames);
        }

        private void nextPage_Click(object sender, EventArgs e)
        {
            getPage(currentpage + 1, prevgames);
        }

        private void mainMenuBack_Click(object sender, EventArgs e)
        {
            gamesList.Visible = false;
            MainMenu.Visible = true;
        }

        private void joinGame(object sender, EventArgs e)
        {
            string name = ((Button)sender).Name;
            int num = name.Last() - '1';
            num = num + ((currentpage - 1) * 4);
            if (prevgames[num].privat == 1)
            {
                if (validPin(pins[num - ((currentpage - 1) * 4)].Text) == false)
                {
                    pins[num - ((currentpage - 1) * 4)].Text = "Invalid";
                    return;
                }
                string response = getData(host + "/joinGame?id=" + prevgames[num].id + "&name=Smith&pin=" + pins[num - ((currentpage - 1) * 4)].Text);
                JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                if (jsonResponse.status == "okay")
                {
                    int[] b = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                    playGame.Visible = true;
                    gamesList.Visible = false;
                    runGame(jsonResponse.letter, jsonResponse.secret, 1, b);
                }
                else
                {
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                }
            }
            else
            {
                string response = getData(host + "/joinGame?id=" + prevgames[num].id + "&name=Smith");
                JsonProcess jsonResponse = JsonConvert.DeserializeObject<JsonProcess>(response);
                if (jsonResponse.status == "okay")
                {
                    int[] b = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
                    playGame.Visible = true;
                    gamesList.Visible = false;
                    runGame(jsonResponse.letter, jsonResponse.secret, 1, b);
                }
                else
                {
                    MessageBox.Show("Error " + jsonResponse.code.ToString() + " : " + jsonResponse.message, "Critical Warning", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);
                }
            }
        }

    }

    class gameObject
    {
        public string name;
        public string id;
        public string description;
        public int letter;
        public int privat;
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
        public int winner = -1;
    }
}
