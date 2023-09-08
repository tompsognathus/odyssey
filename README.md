# Odyssey
## Combat Encounter
![Combat Encounter](https://raw.githubusercontent.com/tompsognathus/odyssey/main/Screenshots/combat_encounter.png)
## RP Encounter
![RP Encounter](https://raw.githubusercontent.com/tompsognathus/odyssey/main/Screenshots/rp_encounter.png)
## Inventory
![Combat Encounter](https://raw.githubusercontent.com/tompsognathus/odyssey/main/Screenshots/inventory.png)
## Pause Menu
![Combat Encounter](https://raw.githubusercontent.com/tompsognathus/odyssey/main/Screenshots/pause_menu.png)

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
    8. Repeat the relevant steps to set up a second material with the second camera and position it to frame the character's head.
4. Add your skeletal mesh and whatever you need to set that up properly (animations and stuff)
5. Set up your dialogue component - you must at the very least set a Dialogue Participant name if you want the NPC to be able to appear in dialogue. Set the participant avatar to be the new head material you just created.
6. Highlighter component: By default, all static and skeletal meshes get highlighted when the object is interactable. If you only want to highlight specific meshes, check the _Outline Only Tagged Meshes_ checkbox in the Highlighter component, set the _Outline Mesh Tag_ to whatever you want it to be and add the tag to any meshes you want to be highlighted
    
## Interactables
### Creating an Item That Triggers Dialogue

## UI
### Adding a New UI Widget
1. Create a C++ class from UserWidget
2. Create a new widget blueprint and set its parent class to be the class you just created
3. Set up your blueprint widget
4. For any components you want to be able to access from code, use 
```
UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
class UExampleComponent* ExampleComponentName;
```
Make sure the ExampleComponentName matches the name you set in your blueprint.

5. If you need stuff like interactable buttons, you'll want to create a function in your C++ code that you want to be called when the buttons are clicked. Call them something like HandleBtn1Clicked...
6. Next we want to bind the functions you just created to the appropriate events in blueprints. See how this is done in one of the existing blueprints. Any of the menu UI widgets will do
7. Add your widget to the UI Manager code:
   1. In your header file, under UI Widget Assets, you'll need to add an AssetRef variable. This will be a reference to the blueprint you just created. Don't forget to set this in the editor once you're done. The UI Manager is attached to your player character.
   2. Scroll down to UI Widget Functions and add a DisplayYourWidgetName() function.
   3. Scroll down to UI Widgets and add a YourWidgetNameInstance variable. This will be where we store a reference to your widget once we've created it at runtime.
   4. Now go to your cpp file and implement your DisplayYourWidgetName() function. Use DisplayWidget and add whatever other functionality you need.
   5. Find the CreateUIWidgets() function and add your widget...
   6. Add your widget to the AddWidgetsToWidgetSwitcher() function
