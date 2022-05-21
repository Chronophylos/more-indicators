/*

*/

class PAG_StanceVelocityInfo : SCR_InfoDisplayExtended {
	ref PAG_StanceVelocityInfoWidgets widgets;
	
	SCR_CharacterControllerComponent m_CharacterController = null;
	SCR_CharacterDamageManagerComponent m_DamageController = null;
	
	//------------------------------------------------------------------------------------------------
	override bool DisplayStartDrawInit(IEntity owner)
	{
		CreateLayout();
		
		SCR_ChimeraCharacter character = SCR_ChimeraCharacter.Cast(owner);
		if (!character)
			return false;
		
		// Store character contoller
		m_CharacterController = SCR_CharacterControllerComponent.Cast(character.FindComponent(SCR_CharacterControllerComponent));
		if (!m_CharacterController)
			return false;
		
		// Store damage Contact
		
		m_DamageController = SCR_CharacterDamageManagerComponent.Cast(character.FindComponent(SCR_CharacterDamageManagerComponent));
		if (!m_DamageController)
			return false;
	
		return true;
	}
		
	override void DisplayUpdate(IEntity owner, float timeSlice)
	{	
		UpdateStance();
		UpdateSpeed();
		UpdateStamina();
		UpdateHealth();
		UpdateBlood();
	}
	
	//------------------------------------------------------------------------------------------------
	// Create the layout
	//------------------------------------------------------------------------------------------------
	void CreateLayout()
	{		
		// Destroy existing layout
		DestroyLayout();
		
		// Create weapon info layout
		SCR_HUDManagerComponent manager = SCR_HUDManagerComponent.GetHUDManager();
		if (manager)
			m_wRoot = manager.CreateLayout(PAG_StanceVelocityInfoWidgets.s_sLayout, m_eLayer);

		if (!m_wRoot)
			return;
		
		widgets = new PAG_StanceVelocityInfoWidgets();
		widgets.Init(m_wRoot);
	}
	
	//------------------------------------------------------------------------------------------------
	// Destroy the layout
	//------------------------------------------------------------------------------------------------
	void DestroyLayout()
	{
		if (m_wRoot)
			m_wRoot.RemoveFromHierarchy();
			
		m_wRoot = null;
	}
	
	//------------------------------------------------------------------------------------------------
	// Update Speed Indicator
	//------------------------------------------------------------------------------------------------
	void UpdateSpeed()
	{
		if (!m_CharacterController)
			return;
		
		auto dynamicSpeed = m_CharacterController.GetDynamicSpeed();
		widgets.m_Speed.SetCurrent(dynamicSpeed * 100);
	}
	
	//------------------------------------------------------------------------------------------------
	// Update Stance Indicator
	//------------------------------------------------------------------------------------------------
	void UpdateStance()
	{
		if (!m_CharacterController)
			return;
		
		auto dynamicStance = m_CharacterController.GetDynamicStance();
		widgets.m_Stance.SetCurrent(dynamicStance * 100);
	}
		
	//------------------------------------------------------------------------------------------------
	// Update Stamina Indicator
	//------------------------------------------------------------------------------------------------
	void UpdateStamina()
	{
		if (!m_CharacterController)
			return;
		
		auto stamina = m_CharacterController.GetStamina();
		
		// Hide stamina bar if character has stamina disabled
		if (widgets.m_Stamina.IsVisible() && stamina == -1)
		{
			widgets.m_Stamina.SetVisible(false);
			return;
		}
		else if (!widgets.m_Stamina.IsVisible())
		{
			widgets.m_Stamina.SetVisible(true);
		}
		
		widgets.m_Stamina.SetCurrent(stamina * 100);
	}
			
	//------------------------------------------------------------------------------------------------
	// Update Health Indicator
	//------------------------------------------------------------------------------------------------
	void UpdateHealth()
	{
		if (!m_DamageController)
			return;
		
		auto health = m_DamageController.GetHealthScaled();
		widgets.m_Health.SetCurrent(health * 100);
	}
			
	//------------------------------------------------------------------------------------------------
	// Update Blood Indicator
	//------------------------------------------------------------------------------------------------
	void UpdateBlood()
	{
		if (!m_DamageController)
			return;
		
		HitZone hitzone = m_DamageController.GetBloodHitZone();
		auto blood = hitzone.GetHealthScaled();
		widgets.m_Blood.SetCurrent(blood * 100);
	}
}