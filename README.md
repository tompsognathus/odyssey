# Odyssey

## NPCs
### Creating a New NPC
1. Create a child blueprint from BP_NPC in Content/Blueprints/NPCs
2. Set the UIDisplayName to whatever you want to show up in dialogue and the rest of the UI to represent the NPC
3. Set Avatar Material. This is used to display NPCs in combat etc. You will first need to create it:
    1. Go to Content/Blueprints/Avatars and create a new folder for your NPC.
    2. Create a child blueprint from BP_CharacterAvatar.
    3. Copy a render target and render target material asset from one of the existing NPCs and rename them
    4. In your new character avatar blueprint, select the RenderTarget component and set the TextureTarget to the texture asset you just duplicated
    5. Select the SkeletalMesh componenet and set the SkeletalMeshAsset to whatever you need it to be. If you need to add multiple, just add them as children or whatever you need for animations to work.
    6. Set up your animations as either an animation asset or blueprint
    7. Go to your Material asset that you duplicated, select the Texture Sample node and set the texture to be your RenderTarget
4. Add your skeletal mesh and whatever you need to set that up properly (animations and stuff)
5. Set up your dialogue component - you must at the very least set a Dialogue Participant name if you want the NPC to have dialogue.
   
