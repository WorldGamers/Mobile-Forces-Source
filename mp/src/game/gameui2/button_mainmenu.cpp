#include "gameui2_interface.h"
#include "button_mainmenu.h"

#include "vgui/ILocalize.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(Button_MainMenu, Button_MainMenu);

extern CUtlSymbolTable g_ButtonSoundNames;

Button_MainMenu::Button_MainMenu(vgui::Panel* parent, vgui::Panel* pActionSignalTarget, const char* pCmd) : BaseClass(parent, "", "", pActionSignalTarget, pCmd)
{
	Init();
	m_pCmd = pCmd;
}

void Button_MainMenu::SetButtonText(const char* text)
{
	m_ButtonText = GameUI2().GetLocalizedString(text);
}

void Button_MainMenu::SetButtonDescription(const char* description)
{
	m_ButtonDescription = GameUI2().GetLocalizedString(description);
}

void Button_MainMenu::Init()
{
	vgui::HScheme Scheme = vgui::scheme()->LoadSchemeFromFile("resource2/schememainmenu.res", "SchemeMainMenu");
	SetScheme(Scheme);

	m_pAnimController = new vgui::AnimationController(this);
	m_pAnimController->SetScheme(Scheme);
	m_pAnimController->SetProportional(false);

	SetProportional(false);
	SetPaintBorderEnabled(false);
	SetPaintBackgroundEnabled(false);
	SetEnabled(true);
	SetVisible(false);
}

void Button_MainMenu::ApplySchemeSettings(vgui::IScheme* pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

	SetDefaultColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetArmedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetSelectedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetDepressedColor(Color(0, 0, 0, 0), Color(0, 0, 0, 0));
	SetBlinkColor(Color(0, 0, 0, 0));
	SetArmedSound("interface/ui/button_over.wav");
	SetDepressedSound("interface/ui/button_click.wav");
	SetReleasedSound("interface/ui/button_release.wav");

	m_fWidth = m_fWidthOut = atof(pScheme->GetResourceString("MainMenu.Button.Width.Out"));
	m_fWidthOver = atof(pScheme->GetResourceString("MainMenu.Button.Width.Over"));
	m_fWidthPressed = atof(pScheme->GetResourceString("MainMenu.Button.Width.Pressed"));
	m_fWidthReleased = atof(pScheme->GetResourceString("MainMenu.Button.Width.Released"));

	m_fHeight = m_fHeightOut = atof(pScheme->GetResourceString("MainMenu.Button.Height.Out"));
	m_fHeightOver = atof(pScheme->GetResourceString("MainMenu.Button.Height.Over"));
	m_fHeightPressed = atof(pScheme->GetResourceString("MainMenu.Button.Height.Pressed"));
	m_fHeightReleased = atof(pScheme->GetResourceString("MainMenu.Button.Height.Released"));

	m_fTextOffsetX = atof(pScheme->GetResourceString("MainMenu.Button.Text.OffsetX"));
	m_fTextOffsetY = atof(pScheme->GetResourceString("MainMenu.Button.Text.OffsetY"));

	m_fDescriptionOffsetX = atof(pScheme->GetResourceString("MainMenu.Button.Description.OffsetX"));
	m_fDescriptionOffsetY = atof(pScheme->GetResourceString("MainMenu.Button.Description.OffsetY"));

	m_bDescriptionHideOut = atoi(pScheme->GetResourceString("MainMenu.Button.Description.Hide.Out"));
	m_bDescriptionHideOver = atoi(pScheme->GetResourceString("MainMenu.Button.Description.Hide.Over"));
	m_bDescriptionHidePressed = atoi(pScheme->GetResourceString("MainMenu.Button.Description.Hide.Pressed"));
	m_bDescriptionHideReleased = atoi(pScheme->GetResourceString("MainMenu.Button.Description.Hide.Released"));

	m_fAnimationWidth = atof(pScheme->GetResourceString("MainMenu.Button.Animation.Width"));
	m_fAnimationHeight = atof(pScheme->GetResourceString("MainMenu.Button.Animation.Height"));
	m_fAnimationBackground = atof(pScheme->GetResourceString("MainMenu.Button.Animation.Background"));
	m_fAnimationText = atof(pScheme->GetResourceString("MainMenu.Button.Animation.Text"));
	m_fAnimationDescription = atof(pScheme->GetResourceString("MainMenu.Button.Animation.Description"));

	m_cBackground = m_cBackgroundOut = GetSchemeColor("MainMenu.Button.Background.Out", pScheme);
	m_cBackgroundOver = GetSchemeColor("MainMenu.Button.Background.Over", pScheme);
	m_cBackgroundPressed = GetSchemeColor("MainMenu.Button.Background.Pressed", pScheme);
	m_cBackgroundReleased = GetSchemeColor("MainMenu.Button.Background.Released", pScheme);

	m_cBackgroundOutline = m_cBackgroundOutlineOut = GetSchemeColor("MainMenu.Button.Background.Outline.Out", pScheme);
	m_cBackgroundOutlineOver = GetSchemeColor("MainMenu.Button.Background.Outline.Over", pScheme);
	m_cBackgroundOutlinePressed = GetSchemeColor("MainMenu.Button.Background.Outline.Pressed", pScheme);
	m_cBackgroundOutlineReleased = GetSchemeColor("MainMenu.Button.Background.Outline.Released", pScheme);

	m_cText = m_cTextOut = GetSchemeColor("MainMenu.Button.Text.Out", pScheme);
	m_cTextOver = GetSchemeColor("MainMenu.Button.Text.Over", pScheme);
	m_cTextPressed = GetSchemeColor("MainMenu.Button.Text.Pressed", pScheme);
	m_cTextReleased = GetSchemeColor("MainMenu.Button.Text.Released", pScheme);

	m_cDescription = m_cDescriptionOut = GetSchemeColor("MainMenu.Button.Description.Out", pScheme);
	m_cDescriptionOver = GetSchemeColor("MainMenu.Button.Description.Over", pScheme);
	m_cDescriptionPressed = GetSchemeColor("MainMenu.Button.Description.Pressed", pScheme);
	m_cDescriptionReleased = GetSchemeColor("MainMenu.Button.Description.Released", pScheme);

	m_cBackgroundBlurAlpha = Color(0, 0, 0, 0);
	m_bBackgroundBlurOut = atoi(pScheme->GetResourceString("MainMenu.Button.Background.Blur.Out"));
	m_bBackgroundBlurOver = atoi(pScheme->GetResourceString("MainMenu.Button.Background.Blur.Over"));
	m_bBackgroundBlurPressed = atoi(pScheme->GetResourceString("MainMenu.Button.Background.Blur.Pressed"));
	m_bBackgroundBlurReleased = atoi(pScheme->GetResourceString("MainMenu.Button.Background.Blur.Released"));

	m_fTextFont = pScheme->GetFont("MainMenu.Button.Text.Font");
	m_fDescriptionFont = pScheme->GetFont("MainMenu.Button.Description.Font");

	m_sButtonState = m_sButtonStateOld = Out;
}

void Button_MainMenu::Animations()
{
	if (m_pAnimController != nullptr)
		m_pAnimController->UpdateAnimations(GameUI2().GetTime()); // (gpGlobals->realtime);

	if (m_sButtonStateOld != m_sButtonState && m_pAnimController != nullptr)
	{
		switch (m_sButtonState)
		{
			case Out:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOut, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOut, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundOutline", m_cBackgroundOutlineOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOut, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOut, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundBlurAlpha", m_bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Over:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOver, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOver, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOver, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundOutline", m_cBackgroundOutlineOver, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOver, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOver, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundBlurAlpha", m_bBackgroundBlurOver ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Pressed:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthPressed, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightPressed, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundPressed, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundOutline", m_cBackgroundOutlinePressed, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextPressed, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionPressed, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundBlurAlpha", m_bBackgroundBlurPressed ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			case Released:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthReleased, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightReleased, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundReleased, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundOutline", m_cBackgroundOutlineReleased, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextReleased, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionReleased, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundBlurAlpha", m_bBackgroundBlurReleased ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;

			default:
				m_pAnimController->RunAnimationCommand(this, "m_fWidth", m_fWidthOut, 0.0f, m_fAnimationWidth, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_fHeight", m_fHeightOut, 0.0f, m_fAnimationHeight, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackground", m_cBackgroundOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundOutline", m_cBackgroundOutlineOut, 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cText", m_cTextOut, 0.0f, m_fAnimationText, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cDescription", m_cDescriptionOut, 0.0f, m_fAnimationDescription, vgui::AnimationController::INTERPOLATOR_LINEAR);
				m_pAnimController->RunAnimationCommand(this, "m_cBackgroundBlurAlpha", m_bBackgroundBlurOut ? Color(255, 255, 255, 255) : Color(0, 0, 0, 0), 0.0f, m_fAnimationBackground, vgui::AnimationController::INTERPOLATOR_LINEAR);
				break;
		}

		m_sButtonStateOld = m_sButtonState;
	}

	SetSize(m_fWidth, m_fHeight);
}

void Button_MainMenu::OnThink()
{
	BaseClass::OnThink();

	AdditionalCursorCheck();
	Animations();

	if (IsVisible() == false)
	{
		ConColorMsg(Color(0, 148, 255, 255), "\nMain menu is not visible, running all animations to completion...\n");

		if (m_pAnimController != nullptr)
			m_pAnimController->RunAllAnimationsToCompletion();
	}
}

void Button_MainMenu::DrawButton()
{
	vgui::surface()->DrawSetColor(m_cBackground);
	vgui::surface()->DrawFilledRect(0, 0, m_fWidth + 0, m_fHeight + 0);

	vgui::surface()->DrawSetColor(m_cBackgroundOutline);
	vgui::surface()->DrawOutlinedRect(0, 0, m_fWidth + 0, m_fHeight + 0);
}

void Button_MainMenu::DrawButton_Blur()
{
	vgui::surface()->DrawSetColor(m_cBackgroundBlurAlpha);
	vgui::surface()->DrawFilledRect(0, 0, m_fWidth + 0, m_fHeight + 0);
}

void Button_MainMenu::DrawText()
{
	vgui::surface()->DrawSetTextColor(m_cText);
	vgui::surface()->DrawSetTextFont(m_fTextFont);

	vgui::surface()->GetTextSize(m_fTextFont, m_ButtonText, m_iTextSizeX, m_iTextSizeY);
	m_iTextPositionX = m_fTextOffsetX;
	m_iTextPositionY = m_fHeight / 2 - m_iTextSizeY / 2 + m_fTextOffsetY;

	vgui::surface()->DrawSetTextPos(m_iTextPositionX, m_iTextPositionY);
	vgui::surface()->DrawPrintText(m_ButtonText, wcslen(m_ButtonText));
}

void Button_MainMenu::DrawDescription()
{
	if (m_sButtonState == Out && m_bDescriptionHideOut == true ||
		m_sButtonState == Over && m_bDescriptionHideOver == true ||
		m_sButtonState == Pressed && m_bDescriptionHidePressed == true ||
		m_sButtonState == Released && m_bDescriptionHideReleased == true)
		return;

	vgui::surface()->DrawSetTextColor(m_cDescription);
	vgui::surface()->DrawSetTextFont(m_fDescriptionFont);
	vgui::surface()->DrawSetTextPos(m_iTextPositionX + m_fDescriptionOffsetX, m_iTextPositionY + m_iTextSizeY + m_fDescriptionOffsetY);
	vgui::surface()->DrawPrintText(m_ButtonDescription, wcslen(m_ButtonDescription));
}

void Button_MainMenu::Paint()
{
	BaseClass::Paint();

	DrawButton();
	DrawText();
	DrawDescription();
}

void Button_MainMenu::PaintBlurMask()
{
	BaseClass::PaintBlurMask();
	
	DrawButton_Blur();
}

void Button_MainMenu::OnCursorExited()
{
	BaseClass::OnCursorExited();

	m_sButtonState = Out;
}

void Button_MainMenu::OnCursorEntered()
{
	BaseClass::OnCursorEntered();

	m_sButtonState = Over;
}

void Button_MainMenu::AdditionalCursorCheck()
{
	if (IsCursorOver() == false)
		m_sButtonState = Out;
	else if (IsCursorOver() == true && m_sButtonState == Out)
		m_sButtonState = Over;
}

void Button_MainMenu::OnMousePressed(vgui::MouseCode code)
{
	if (code == MOUSE_LEFT)
	{
		if (m_sDepressedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sDepressedSoundName));

		m_sButtonState = Pressed;
	}
}

void Button_MainMenu::OnMouseReleased(vgui::MouseCode code)
{
	if (code == MOUSE_LEFT)
	{
		if (m_sReleasedSoundName != UTL_INVAL_SYMBOL)
			vgui::surface()->PlaySound(g_ButtonSoundNames.String(m_sReleasedSoundName));

		m_sButtonState = Released;

		GetParent()->OnCommand(m_pCmd);
	}
}