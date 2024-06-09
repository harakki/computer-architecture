#ifndef MY_READ_KEY_H
#define MY_READ_KEY_H

enum keys
{
  F5_KEY,          /* "^[[15~" */
  F6_KEY,          /* "^[[17~" */
  ESC_KEY,         /* "^[" */
  ENTER_KEY,       /* "^M" */
  LEFT_ARROW_KEY,  /* "^[[D" */
  RIGHT_ARROW_KEY, /* "^[[C" */
  UP_ARROW_KEY,    /* "^[[A" */
  DOWN_ARROW_KEY,  /* "^[[B" */
  LOAD_KEY,        /* "L" */
  SAVE_KEY,        /* "S" */
  RUN_KEY,         /* "R" */
  STEP_KEY,        /* "T" */
  RESET_KEY,       /* "I" */
  QUIT_KEY,        /* "Q" */
  UNKNOWN_KEY
};

int rk_readKey (enum keys *key);
int rk_saveMyTerm (void);
int rk_restoreMyTerm (void);
int rk_myTermRegime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readValue (int *value, int timeout);

#endif /* MY_READ_KEY_H */
