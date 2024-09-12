# Proposal
import tkinter as tk
from tkinter import messagebox
import random

def typewriter_effect(label, text, delay=100, callback=None):
    """Simulate a typing effect for the text on the label."""
    def update_text(index):
        if index < len(text):
            label.config(text=text[:index + 1])
            root.after(delay, update_text, index + 1)
        elif callback:
            # Call the callback function after typing is complete
            root.after(500, callback)
    
    update_text(0)

def handle_response(answer):
    """Handle the response from the yes/no buttons."""
    if answer:
        messagebox.showinfo("Yay!", "I'm so glad you said yes! 😊")
    else:
        messagebox.showinfo("No worries!", "That's okay! I'll always cherish our friendship. 😊")

def move_no_button(event):
    """Move the 'No' button to a new position quickly within the frame bounds, avoiding overlap with 'Yes' button."""
    # Temporarily disable the 'No' button to prevent clicks during movement
    no_button.config(state=tk.DISABLED)
    
    button_width = no_button.winfo_width()
    button_height = no_button.winfo_height()
    frame_width = button_frame.winfo_width()
    frame_height = button_frame.winfo_height()
    

    yes_x = yes_button.winfo_x()
    yes_y = yes_button.winfo_y()
    yes_width = yes_button.winfo_width()
    yes_height = yes_button.winfo_height()
    
    while True:
    
        new_x = random.randint(0, frame_width - button_width)
        new_y = random.randint(0, frame_height - button_height)
        
    
        if (not (new_x + button_width < yes_x or new_x > yes_x + yes_width or
                 new_y + button_height < yes_y or new_y > yes_y + yes_height)):
            # If overlapping, continue to generate a new position
            continue
        

        no_button.place(x=new_x, y=new_y)
        break
    
    root.after(200, lambda: no_button.config(state=tk.NORMAL))

def open_second_window():
    """Open a new window with a typing effect for the proposal message and yes/no buttons."""
    second_window = tk.Toplevel(root)
    second_window.title("Proposal Message")
    second_window.geometry("600x400")
    second_window.configure(bg="#e0f7fa")
    
    # Create a label for the typing effect
    message_label = tk.Label(second_window, text="", font=("Helvetica", 14), fg="#004d40", bg="#e0f7fa", wraplength=500)
    message_label.pack(pady=30, padx=20)

    # Create a frame for the buttons
    global button_frame, yes_button, no_button
    button_frame = tk.Frame(second_window, bg="#e0f7fa", width=300, height=100)
    button_frame.pack(pady=20)
    
    yes_button = tk.Button(button_frame, text="Yes", font=("Helvetica", 12), fg="white", bg="#4caf50", command=lambda: handle_response(True))
    yes_button.pack(side=tk.LEFT, padx=20)

    no_button = tk.Button(button_frame, text="No", font=("Helvetica", 12), fg="white", bg="#f44336")
    no_button.pack(side=tk.LEFT, padx=20)

    # Bind the move function to the 'No' button click event
    no_button.bind("<Button-1>", move_no_button)

    # Start the typing effect
    message = ("Hey Rose💖,\n\n"
               "I’ve been thinking about you a lot lately...\n\n"
               "You make me smile like no one else can.\n\n"
               "Would you do me the honor of being my girlfriend?\n\n"
               "I promise to always cherish and support you.\n\n"
               "What do you say? 💖")
    
    typewriter_effect(message_label, message)

def create_proposal_window():
    """Create and display the proposal window with a designed first screen and 3D blue circular button."""
    global root
    root = tk.Tk()
    root.title("Proposal")

    # Set window size and background color
    root.geometry("600x400")
    root.configure(bg="#e0f7fa")  # Light blue background

    # Create a styled header label
    header = tk.Label(root, text="A Special Question Just for You", 
                      font=("Comic Sans MS", 20, "bold"), fg="#00796b", bg="#e0f7fa")
    header.pack(pady=30)

    # Create a romantic message label
    message = tk.Label(root, text="Click the button below to see something special!", 
                       font=("Helvetica", 14), fg="#004d40", bg="#e0f7fa")
    message.pack(pady=20)

    # Create a canvas for the circular button
    canvas = tk.Canvas(root, width=200, height=200, bg="#e0f7fa", bd=0, highlightthickness=0)
    canvas.pack(pady=20)

    # Draw a 3D-looking circular button on the canvas
    # Draw outer shadow
    canvas.create_oval(20, 20, 180, 180, fill="#004d40", outline="#004d40")
    # Draw inner button
    canvas.create_oval(30, 30, 170, 170, fill="#2196f3", outline="#1e88e5")
    # Draw button highlight (simulating a 3D effect)
    canvas.create_oval(40, 40, 160, 160, fill="#64b5f6", outline="#42a5f5")

    # Create a transparent rectangle over the button to capture clicks
    canvas.create_rectangle(20, 20, 180, 180, fill="", outline="", tags="button_area")

    # Bind the click event to the button_area
    canvas.tag_bind("button_area", "<Button-1>", lambda e: open_second_window())

    # Run the Tkinter event loop
    root.mainloop()

if __name__ == "__main__":
    create_proposal_window()
