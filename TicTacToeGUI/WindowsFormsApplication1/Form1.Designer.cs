namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.StartGame = new System.Windows.Forms.Button();
            this.JoinGame = new System.Windows.Forms.Button();
            this.Help = new System.Windows.Forms.Button();
            this.Credits = new System.Windows.Forms.Button();
            this.MainMenu = new System.Windows.Forms.Panel();
            this.StartGameMenu = new System.Windows.Forms.Panel();
            this.GetStarted = new System.Windows.Forms.Button();
            this.GoBack = new System.Windows.Forms.Button();
            this.pinBox = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.pickNo = new System.Windows.Forms.CheckBox();
            this.label5 = new System.Windows.Forms.Label();
            this.pickYes = new System.Windows.Forms.CheckBox();
            this.Description = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.pickO = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.pickX = new System.Windows.Forms.CheckBox();
            this.yourName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.playGame = new System.Windows.Forms.Panel();
            this.ExitGame = new System.Windows.Forms.Button();
            this.whatTurn = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.play1 = new System.Windows.Forms.Button();
            this.play2 = new System.Windows.Forms.Button();
            this.play3 = new System.Windows.Forms.Button();
            this.play5 = new System.Windows.Forms.Button();
            this.play8 = new System.Windows.Forms.Button();
            this.play7 = new System.Windows.Forms.Button();
            this.play4 = new System.Windows.Forms.Button();
            this.play6 = new System.Windows.Forms.Button();
            this.play9 = new System.Windows.Forms.Button();
            this.MainMenu.SuspendLayout();
            this.StartGameMenu.SuspendLayout();
            this.playGame.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // StartGame
            // 
            this.StartGame.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartGame.Location = new System.Drawing.Point(65, 40);
            this.StartGame.Name = "StartGame";
            this.StartGame.Size = new System.Drawing.Size(408, 71);
            this.StartGame.TabIndex = 0;
            this.StartGame.Text = "Start a new game";
            this.StartGame.UseVisualStyleBackColor = true;
            this.StartGame.MouseCaptureChanged += new System.EventHandler(this.startGame);
            // 
            // JoinGame
            // 
            this.JoinGame.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.JoinGame.Location = new System.Drawing.Point(65, 158);
            this.JoinGame.Name = "JoinGame";
            this.JoinGame.Size = new System.Drawing.Size(408, 71);
            this.JoinGame.TabIndex = 1;
            this.JoinGame.Text = "Join a game";
            this.JoinGame.UseVisualStyleBackColor = true;
            // 
            // Help
            // 
            this.Help.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Help.Location = new System.Drawing.Point(65, 280);
            this.Help.Name = "Help";
            this.Help.Size = new System.Drawing.Size(408, 71);
            this.Help.TabIndex = 2;
            this.Help.Text = "Help";
            this.Help.UseVisualStyleBackColor = true;
            // 
            // Credits
            // 
            this.Credits.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Credits.Location = new System.Drawing.Point(65, 392);
            this.Credits.Name = "Credits";
            this.Credits.Size = new System.Drawing.Size(408, 71);
            this.Credits.TabIndex = 3;
            this.Credits.Text = "View credits";
            this.Credits.UseVisualStyleBackColor = true;
            // 
            // MainMenu
            // 
            this.MainMenu.Controls.Add(this.Credits);
            this.MainMenu.Controls.Add(this.Help);
            this.MainMenu.Controls.Add(this.JoinGame);
            this.MainMenu.Controls.Add(this.StartGame);
            this.MainMenu.Location = new System.Drawing.Point(53, 11);
            this.MainMenu.Name = "MainMenu";
            this.MainMenu.Size = new System.Drawing.Size(530, 478);
            this.MainMenu.TabIndex = 10;
            // 
            // StartGameMenu
            // 
            this.StartGameMenu.Controls.Add(this.GetStarted);
            this.StartGameMenu.Controls.Add(this.GoBack);
            this.StartGameMenu.Controls.Add(this.pinBox);
            this.StartGameMenu.Controls.Add(this.label6);
            this.StartGameMenu.Controls.Add(this.pickNo);
            this.StartGameMenu.Controls.Add(this.label5);
            this.StartGameMenu.Controls.Add(this.pickYes);
            this.StartGameMenu.Controls.Add(this.Description);
            this.StartGameMenu.Controls.Add(this.label4);
            this.StartGameMenu.Controls.Add(this.pickO);
            this.StartGameMenu.Controls.Add(this.label3);
            this.StartGameMenu.Controls.Add(this.pickX);
            this.StartGameMenu.Controls.Add(this.yourName);
            this.StartGameMenu.Controls.Add(this.label2);
            this.StartGameMenu.Controls.Add(this.label1);
            this.StartGameMenu.Location = new System.Drawing.Point(53, 12);
            this.StartGameMenu.Name = "StartGameMenu";
            this.StartGameMenu.Size = new System.Drawing.Size(527, 478);
            this.StartGameMenu.TabIndex = 4;
            // 
            // GetStarted
            // 
            this.GetStarted.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GetStarted.Location = new System.Drawing.Point(248, 411);
            this.GetStarted.Name = "GetStarted";
            this.GetStarted.Size = new System.Drawing.Size(243, 51);
            this.GetStarted.TabIndex = 14;
            this.GetStarted.Text = "Start Game";
            this.GetStarted.UseVisualStyleBackColor = true;
            this.GetStarted.Click += new System.EventHandler(this.GetStarted_Click);
            // 
            // GoBack
            // 
            this.GoBack.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GoBack.Location = new System.Drawing.Point(49, 411);
            this.GoBack.Name = "GoBack";
            this.GoBack.Size = new System.Drawing.Size(183, 51);
            this.GoBack.TabIndex = 13;
            this.GoBack.Text = "Go Back";
            this.GoBack.UseVisualStyleBackColor = true;
            this.GoBack.Click += new System.EventHandler(this.GoBack_Click);
            // 
            // pinBox
            // 
            this.pinBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pinBox.Location = new System.Drawing.Point(359, 354);
            this.pinBox.Name = "pinBox";
            this.pinBox.Size = new System.Drawing.Size(111, 31);
            this.pinBox.TabIndex = 12;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(39, 354);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(316, 31);
            this.label6.TabIndex = 11;
            this.label6.Text = "If yes, enter a 4 digit pin :";
            // 
            // pickNo
            // 
            this.pickNo.AutoSize = true;
            this.pickNo.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pickNo.Location = new System.Drawing.Point(359, 298);
            this.pickNo.Name = "pickNo";
            this.pickNo.Size = new System.Drawing.Size(58, 29);
            this.pickNo.TabIndex = 10;
            this.pickNo.Text = "No";
            this.pickNo.UseVisualStyleBackColor = true;
            this.pickNo.CheckedChanged += new System.EventHandler(this.pickNo_CheckedChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(39, 298);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(201, 31);
            this.label5.TabIndex = 9;
            this.label5.Text = "Private Game : ";
            // 
            // pickYes
            // 
            this.pickYes.AutoSize = true;
            this.pickYes.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pickYes.Location = new System.Drawing.Point(259, 298);
            this.pickYes.Name = "pickYes";
            this.pickYes.Size = new System.Drawing.Size(69, 29);
            this.pickYes.TabIndex = 8;
            this.pickYes.Text = "Yes";
            this.pickYes.UseVisualStyleBackColor = true;
            this.pickYes.CheckedChanged += new System.EventHandler(this.pickYes_CheckedChanged);
            // 
            // Description
            // 
            this.Description.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Description.Location = new System.Drawing.Point(45, 243);
            this.Description.Name = "Description";
            this.Description.Size = new System.Drawing.Size(446, 31);
            this.Description.TabIndex = 7;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(144, 198);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(253, 31);
            this.label4.TabIndex = 6;
            this.label4.Text = "Game Description : ";
            // 
            // pickO
            // 
            this.pickO.AutoSize = true;
            this.pickO.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pickO.Location = new System.Drawing.Point(359, 144);
            this.pickO.Name = "pickO";
            this.pickO.Size = new System.Drawing.Size(47, 29);
            this.pickO.TabIndex = 5;
            this.pickO.Text = "O";
            this.pickO.UseVisualStyleBackColor = true;
            this.pickO.CheckedChanged += new System.EventHandler(this.pickO_CheckedChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(39, 144);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(233, 31);
            this.label3.TabIndex = 4;
            this.label3.Text = "Letter to start as : ";
            // 
            // pickX
            // 
            this.pickX.AutoSize = true;
            this.pickX.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pickX.Location = new System.Drawing.Point(292, 144);
            this.pickX.Name = "pickX";
            this.pickX.Size = new System.Drawing.Size(45, 29);
            this.pickX.TabIndex = 3;
            this.pickX.Text = "X";
            this.pickX.UseVisualStyleBackColor = true;
            this.pickX.CheckedChanged += new System.EventHandler(this.pickX_CheckedChanged);
            // 
            // yourName
            // 
            this.yourName.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.yourName.Location = new System.Drawing.Point(232, 94);
            this.yourName.Name = "yourName";
            this.yourName.Size = new System.Drawing.Size(212, 31);
            this.yourName.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(39, 94);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(172, 31);
            this.label2.TabIndex = 1;
            this.label2.Text = "Your Name : ";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(39, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(452, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "Enter the details of your game below";
            // 
            // playGame
            // 
            this.playGame.Controls.Add(this.play9);
            this.playGame.Controls.Add(this.play6);
            this.playGame.Controls.Add(this.play4);
            this.playGame.Controls.Add(this.play7);
            this.playGame.Controls.Add(this.play8);
            this.playGame.Controls.Add(this.play5);
            this.playGame.Controls.Add(this.play3);
            this.playGame.Controls.Add(this.play2);
            this.playGame.Controls.Add(this.play1);
            this.playGame.Controls.Add(this.pictureBox1);
            this.playGame.Controls.Add(this.ExitGame);
            this.playGame.Controls.Add(this.whatTurn);
            this.playGame.Location = new System.Drawing.Point(50, 9);
            this.playGame.Name = "playGame";
            this.playGame.Size = new System.Drawing.Size(527, 478);
            this.playGame.TabIndex = 11;
            this.playGame.Visible = false;
            // 
            // ExitGame
            // 
            this.ExitGame.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ExitGame.Location = new System.Drawing.Point(45, 411);
            this.ExitGame.Name = "ExitGame";
            this.ExitGame.Size = new System.Drawing.Size(446, 51);
            this.ExitGame.TabIndex = 14;
            this.ExitGame.Text = "Exit Game";
            this.ExitGame.UseVisualStyleBackColor = true;
            // 
            // whatTurn
            // 
            this.whatTurn.AutoSize = true;
            this.whatTurn.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.whatTurn.Location = new System.Drawing.Point(197, 24);
            this.whatTurn.Name = "whatTurn";
            this.whatTurn.Size = new System.Drawing.Size(134, 31);
            this.whatTurn.TabIndex = 0;
            this.whatTurn.Text = "Your Turn";
            this.whatTurn.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::WindowsFormsApplication1.Properties.Resources.TicTackBack_400x4001;
            this.pictureBox1.InitialImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.InitialImage")));
            this.pictureBox1.Location = new System.Drawing.Point(52, 77);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(419, 310);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 15;
            this.pictureBox1.TabStop = false;
            // 
            // play1
            // 
            this.play1.Location = new System.Drawing.Point(60, 89);
            this.play1.Name = "play1";
            this.play1.Size = new System.Drawing.Size(102, 71);
            this.play1.TabIndex = 16;
            this.play1.UseVisualStyleBackColor = true;
            // 
            // play2
            // 
            this.play2.Location = new System.Drawing.Point(193, 89);
            this.play2.Name = "play2";
            this.play2.Size = new System.Drawing.Size(128, 71);
            this.play2.TabIndex = 17;
            this.play2.UseVisualStyleBackColor = true;
            // 
            // play3
            // 
            this.play3.Location = new System.Drawing.Point(346, 89);
            this.play3.Name = "play3";
            this.play3.Size = new System.Drawing.Size(113, 71);
            this.play3.TabIndex = 18;
            this.play3.UseVisualStyleBackColor = true;
            // 
            // play5
            // 
            this.play5.Location = new System.Drawing.Point(193, 187);
            this.play5.Name = "play5";
            this.play5.Size = new System.Drawing.Size(128, 89);
            this.play5.TabIndex = 19;
            this.play5.UseVisualStyleBackColor = true;
            // 
            // play8
            // 
            this.play8.Location = new System.Drawing.Point(193, 301);
            this.play8.Name = "play8";
            this.play8.Size = new System.Drawing.Size(128, 77);
            this.play8.TabIndex = 20;
            this.play8.UseVisualStyleBackColor = true;
            // 
            // play7
            // 
            this.play7.Location = new System.Drawing.Point(59, 301);
            this.play7.Name = "play7";
            this.play7.Size = new System.Drawing.Size(103, 77);
            this.play7.TabIndex = 21;
            this.play7.UseVisualStyleBackColor = true;
            // 
            // play4
            // 
            this.play4.Location = new System.Drawing.Point(59, 187);
            this.play4.Name = "play4";
            this.play4.Size = new System.Drawing.Size(103, 89);
            this.play4.TabIndex = 22;
            this.play4.UseVisualStyleBackColor = true;
            // 
            // play6
            // 
            this.play6.Location = new System.Drawing.Point(346, 188);
            this.play6.Name = "play6";
            this.play6.Size = new System.Drawing.Size(113, 89);
            this.play6.TabIndex = 23;
            this.play6.UseVisualStyleBackColor = true;
            // 
            // play9
            // 
            this.play9.Location = new System.Drawing.Point(346, 301);
            this.play9.Name = "play9";
            this.play9.Size = new System.Drawing.Size(113, 77);
            this.play9.TabIndex = 24;
            this.play9.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(664, 529);
            this.Controls.Add(this.playGame);
            this.Controls.Add(this.StartGameMenu);
            this.Controls.Add(this.MainMenu);
            this.Name = "Form1";
            this.Text = "TicTacToe";
            this.MainMenu.ResumeLayout(false);
            this.StartGameMenu.ResumeLayout(false);
            this.StartGameMenu.PerformLayout();
            this.playGame.ResumeLayout(false);
            this.playGame.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button StartGame;
        private System.Windows.Forms.Button JoinGame;
        private System.Windows.Forms.Button Help;
        private System.Windows.Forms.Button Credits;
        private System.Windows.Forms.Panel MainMenu;
        private System.Windows.Forms.Panel StartGameMenu;
        private System.Windows.Forms.Button GetStarted;
        private System.Windows.Forms.Button GoBack;
        private System.Windows.Forms.TextBox pinBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.CheckBox pickNo;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox pickYes;
        private System.Windows.Forms.TextBox Description;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox pickO;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox pickX;
        private System.Windows.Forms.TextBox yourName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel playGame;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button ExitGame;
        private System.Windows.Forms.Label whatTurn;
        private System.Windows.Forms.Button play6;
        private System.Windows.Forms.Button play4;
        private System.Windows.Forms.Button play7;
        private System.Windows.Forms.Button play8;
        private System.Windows.Forms.Button play5;
        private System.Windows.Forms.Button play3;
        private System.Windows.Forms.Button play2;
        private System.Windows.Forms.Button play1;
        private System.Windows.Forms.Button play9;

    }
}

