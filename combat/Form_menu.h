#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

enum ChoixMenu 
{
	AUCUN,
	OPTIONS,
	INSTRUCTIONS,
	APROPOS,
	RETOURJEU,
	QUITTERJEU
};


namespace combat {

	/// <summary>
	/// Summary for Form_menu
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form_menu : public System::Windows::Forms::Form
	{
	public:
		static ChoixMenu choixMenu;

		Form_menu(void)
		{
			choixMenu = AUCUN;
			InitializeComponent();
			ShowDialog();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form_menu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  options;
	private: System::Windows::Forms::Button^  instructions;
	private: System::Windows::Forms::Button^  apropos;
	private: System::Windows::Forms::Button^  retourJeu;
	private: System::Windows::Forms::Button^  quitterJeu;
	protected: 





	protected: 


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->options = (gcnew System::Windows::Forms::Button());
			this->instructions = (gcnew System::Windows::Forms::Button());
			this->apropos = (gcnew System::Windows::Forms::Button());
			this->retourJeu = (gcnew System::Windows::Forms::Button());
			this->quitterJeu = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// options
			// 
			this->options->Location = System::Drawing::Point(56, 26);
			this->options->Name = L"options";
			this->options->Size = System::Drawing::Size(130, 28);
			this->options->TabIndex = 0;
			this->options->Text = L"Options";
			this->options->UseVisualStyleBackColor = true;
			this->options->Click += gcnew System::EventHandler(this, &Form_menu::options_Click);
			// 
			// instructions
			// 
			this->instructions->Location = System::Drawing::Point(56, 78);
			this->instructions->Name = L"instructions";
			this->instructions->Size = System::Drawing::Size(130, 28);
			this->instructions->TabIndex = 1;
			this->instructions->Text = L"Comment jouer";
			this->instructions->UseVisualStyleBackColor = true;
			this->instructions->Click += gcnew System::EventHandler(this, &Form_menu::instructions_Click);
			// 
			// apropos
			// 
			this->apropos->Location = System::Drawing::Point(56, 133);
			this->apropos->Name = L"apropos";
			this->apropos->Size = System::Drawing::Size(130, 28);
			this->apropos->TabIndex = 2;
			this->apropos->Text = L"A propos";
			this->apropos->UseVisualStyleBackColor = true;
			this->apropos->Click += gcnew System::EventHandler(this, &Form_menu::apropos_Click);
			// 
			// retourJeu
			// 
			this->retourJeu->Location = System::Drawing::Point(56, 190);
			this->retourJeu->Name = L"retourJeu";
			this->retourJeu->Size = System::Drawing::Size(130, 28);
			this->retourJeu->TabIndex = 3;
			this->retourJeu->Text = L"Retour au jeu";
			this->retourJeu->UseVisualStyleBackColor = true;
			this->retourJeu->Click += gcnew System::EventHandler(this, &Form_menu::retourJeu_Click);
			// 
			// quitterJeu
			// 
			this->quitterJeu->Location = System::Drawing::Point(56, 246);
			this->quitterJeu->Name = L"quitterJeu";
			this->quitterJeu->Size = System::Drawing::Size(130, 28);
			this->quitterJeu->TabIndex = 4;
			this->quitterJeu->Text = L"Quitter le jeu";
			this->quitterJeu->UseVisualStyleBackColor = true;
			this->quitterJeu->Click += gcnew System::EventHandler(this, &Form_menu::quitterJeu_Click);
			// 
			// Form_menu
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(241, 298);
			this->ControlBox = false;
			this->Controls->Add(this->quitterJeu);
			this->Controls->Add(this->retourJeu);
			this->Controls->Add(this->apropos);
			this->Controls->Add(this->instructions);
			this->Controls->Add(this->options);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Name = L"Form_menu";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MENU";
			this->ResumeLayout(false);

		}
#pragma endregion
	
private: System::Void options_Click(System::Object^  sender, System::EventArgs^  e) {
				choixMenu=OPTIONS;
				this->Close();
			}
private: System::Void instructions_Click(System::Object^  sender, System::EventArgs^  e) {
				choixMenu=INSTRUCTIONS;
				this->Close();
			}
private: System::Void apropos_Click(System::Object^  sender, System::EventArgs^  e) {
				choixMenu=APROPOS;
				this->Close();
			}
private: System::Void retourJeu_Click(System::Object^  sender, System::EventArgs^  e) {
				choixMenu=RETOURJEU;
				this->Close();
			}
private: System::Void quitterJeu_Click(System::Object^  sender, System::EventArgs^  e) {
				choixMenu=QUITTERJEU;
				this->Close();
			}
};
}
