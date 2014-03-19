namespace Editor
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
            this.quadGroupBox = new System.Windows.Forms.GroupBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.randomizeCheck = new System.Windows.Forms.CheckBox();
            this.removeEntity = new System.Windows.Forms.Button();
            this.addEntity = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.possibleEntities = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.worldGroupBox = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.quadHeight = new System.Windows.Forms.NumericUpDown();
            this.quadWidth = new System.Windows.Forms.NumericUpDown();
            this.numRows = new System.Windows.Forms.NumericUpDown();
            this.numCols = new System.Windows.Forms.NumericUpDown();
            this.panel1 = new System.Windows.Forms.Panel();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.panelleft = new System.Windows.Forms.Panel();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown3 = new System.Windows.Forms.NumericUpDown();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.quadGroupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.worldGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.quadHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.quadWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRows)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCols)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panelleft.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).BeginInit();
            this.SuspendLayout();
            // 
            // quadGroupBox
            // 
            this.quadGroupBox.Controls.Add(this.groupBox1);
            this.quadGroupBox.Controls.Add(this.randomizeCheck);
            this.quadGroupBox.Controls.Add(this.removeEntity);
            this.quadGroupBox.Controls.Add(this.addEntity);
            this.quadGroupBox.Controls.Add(this.label2);
            this.quadGroupBox.Controls.Add(this.numericUpDown1);
            this.quadGroupBox.Controls.Add(this.label1);
            this.quadGroupBox.Controls.Add(this.comboBox1);
            this.quadGroupBox.Controls.Add(this.possibleEntities);
            this.quadGroupBox.Controls.Add(this.listBox1);
            this.quadGroupBox.Location = new System.Drawing.Point(23, 170);
            this.quadGroupBox.Name = "quadGroupBox";
            this.quadGroupBox.Size = new System.Drawing.Size(287, 369);
            this.quadGroupBox.TabIndex = 2;
            this.quadGroupBox.TabStop = false;
            this.quadGroupBox.Text = "Selected Quad";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.numericUpDown3);
            this.groupBox1.Controls.Add(this.numericUpDown2);
            this.groupBox1.Location = new System.Drawing.Point(66, 256);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(160, 94);
            this.groupBox1.TabIndex = 7;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Position";
            // 
            // randomizeCheck
            // 
            this.randomizeCheck.AutoSize = true;
            this.randomizeCheck.Location = new System.Drawing.Point(90, 233);
            this.randomizeCheck.Name = "randomizeCheck";
            this.randomizeCheck.Size = new System.Drawing.Size(79, 17);
            this.randomizeCheck.TabIndex = 6;
            this.randomizeCheck.Text = "Randomize";
            this.randomizeCheck.UseVisualStyleBackColor = true;
            // 
            // removeEntity
            // 
            this.removeEntity.Location = new System.Drawing.Point(257, 69);
            this.removeEntity.Name = "removeEntity";
            this.removeEntity.Size = new System.Drawing.Size(24, 23);
            this.removeEntity.TabIndex = 4;
            this.removeEntity.Text = "-";
            this.removeEntity.UseVisualStyleBackColor = true;
            // 
            // addEntity
            // 
            this.addEntity.Location = new System.Drawing.Point(257, 40);
            this.addEntity.Name = "addEntity";
            this.addEntity.Size = new System.Drawing.Size(24, 23);
            this.addEntity.TabIndex = 4;
            this.addEntity.Text = "+";
            this.addEntity.UseVisualStyleBackColor = true;
            this.addEntity.Click += new System.EventHandler(this.addEntity_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(48, 191);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(79, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Amount (1 - 20)";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(133, 189);
            this.numericUpDown1.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDown1.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(120, 20);
            this.numericUpDown1.TabIndex = 4;
            this.numericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(94, 164);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Entity";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(133, 161);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 21);
            this.comboBox1.TabIndex = 2;
            // 
            // possibleEntities
            // 
            this.possibleEntities.AutoSize = true;
            this.possibleEntities.Location = new System.Drawing.Point(94, 24);
            this.possibleEntities.Name = "possibleEntities";
            this.possibleEntities.Size = new System.Drawing.Size(83, 13);
            this.possibleEntities.TabIndex = 1;
            this.possibleEntities.Text = "Possible Entities";
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(30, 40);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(224, 95);
            this.listBox1.TabIndex = 0;
            // 
            // worldGroupBox
            // 
            this.worldGroupBox.Controls.Add(this.label6);
            this.worldGroupBox.Controls.Add(this.label5);
            this.worldGroupBox.Controls.Add(this.label4);
            this.worldGroupBox.Controls.Add(this.label3);
            this.worldGroupBox.Controls.Add(this.quadHeight);
            this.worldGroupBox.Controls.Add(this.quadWidth);
            this.worldGroupBox.Controls.Add(this.numRows);
            this.worldGroupBox.Controls.Add(this.numCols);
            this.worldGroupBox.Location = new System.Drawing.Point(72, 18);
            this.worldGroupBox.Name = "worldGroupBox";
            this.worldGroupBox.Size = new System.Drawing.Size(177, 130);
            this.worldGroupBox.TabIndex = 3;
            this.worldGroupBox.TabStop = false;
            this.worldGroupBox.Text = "World Info";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(46, 73);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(34, 13);
            this.label6.TabIndex = 7;
            this.label6.Text = "Rows";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(36, 99);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 13);
            this.label5.TabIndex = 6;
            this.label5.Text = "Columns";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(16, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(67, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Quad Height";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 21);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Quad Width";
            // 
            // quadHeight
            // 
            this.quadHeight.Location = new System.Drawing.Point(86, 45);
            this.quadHeight.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.quadHeight.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.quadHeight.Name = "quadHeight";
            this.quadHeight.Size = new System.Drawing.Size(70, 20);
            this.quadHeight.TabIndex = 3;
            this.quadHeight.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.quadHeight.ValueChanged += new System.EventHandler(this.quadHeight_ValueChanged);
            // 
            // quadWidth
            // 
            this.quadWidth.Location = new System.Drawing.Point(86, 19);
            this.quadWidth.Maximum = new decimal(new int[] {
            500,
            0,
            0,
            0});
            this.quadWidth.Minimum = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.quadWidth.Name = "quadWidth";
            this.quadWidth.Size = new System.Drawing.Size(70, 20);
            this.quadWidth.TabIndex = 2;
            this.quadWidth.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.quadWidth.ValueChanged += new System.EventHandler(this.quadWidth_ValueChanged);
            // 
            // numRows
            // 
            this.numRows.Location = new System.Drawing.Point(86, 71);
            this.numRows.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numRows.Name = "numRows";
            this.numRows.Size = new System.Drawing.Size(70, 20);
            this.numRows.TabIndex = 1;
            this.numRows.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numRows.ValueChanged += new System.EventHandler(this.numRows_ValueChanged);
            // 
            // numCols
            // 
            this.numCols.Location = new System.Drawing.Point(86, 97);
            this.numCols.Minimum = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numCols.Name = "numCols";
            this.numCols.Size = new System.Drawing.Size(70, 20);
            this.numCols.TabIndex = 0;
            this.numCols.Value = new decimal(new int[] {
            4,
            0,
            0,
            0});
            this.numCols.ValueChanged += new System.EventHandler(this.numCols_ValueChanged);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(656, 689);
            this.panel1.TabIndex = 0;
            this.panel1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseClick);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
            this.splitContainer1.IsSplitterFixed = true;
            this.splitContainer1.Location = new System.Drawing.Point(0, 24);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.panelleft);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.panel1);
            this.splitContainer1.Size = new System.Drawing.Size(989, 689);
            this.splitContainer1.SplitterDistance = 329;
            this.splitContainer1.TabIndex = 5;
            // 
            // panelleft
            // 
            this.panelleft.AutoScroll = true;
            this.panelleft.AutoScrollMinSize = new System.Drawing.Size(329, 650);
            this.panelleft.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelleft.Controls.Add(this.quadGroupBox);
            this.panelleft.Controls.Add(this.worldGroupBox);
            this.panelleft.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panelleft.Location = new System.Drawing.Point(0, 0);
            this.panelleft.Name = "panelleft";
            this.panelleft.Size = new System.Drawing.Size(329, 689);
            this.panelleft.TabIndex = 0;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(989, 24);
            this.menuStrip1.TabIndex = 6;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(68, 27);
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(61, 20);
            this.numericUpDown2.TabIndex = 0;
            // 
            // numericUpDown3
            // 
            this.numericUpDown3.Location = new System.Drawing.Point(68, 53);
            this.numericUpDown3.Name = "numericUpDown3";
            this.numericUpDown3.Size = new System.Drawing.Size(61, 20);
            this.numericUpDown3.TabIndex = 1;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(48, 29);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(14, 13);
            this.label7.TabIndex = 2;
            this.label7.Text = "X";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(48, 55);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(14, 13);
            this.label8.TabIndex = 3;
            this.label8.Text = "Y";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(989, 713);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.quadGroupBox.ResumeLayout(false);
            this.quadGroupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.worldGroupBox.ResumeLayout(false);
            this.worldGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.quadHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.quadWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numRows)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numCols)).EndInit();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.panelleft.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox quadGroupBox;
        private System.Windows.Forms.Label possibleEntities;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button removeEntity;
        private System.Windows.Forms.Button addEntity;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.GroupBox worldGroupBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown quadHeight;
        private System.Windows.Forms.NumericUpDown quadWidth;
        private System.Windows.Forms.NumericUpDown numRows;
        private System.Windows.Forms.NumericUpDown numCols;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox randomizeCheck;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel panelleft;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.NumericUpDown numericUpDown3;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
    }
}

