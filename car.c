#include <Elementary.h>

Evas_Object *box, *en1, *en2;
Ecore_Timer *timer;
int num_loop = 0;
int timer_loop = 0;
Evas_Object *btn[50];
int btn_pos[50];
int num = 0;

Eina_Bool
_timer_cb(void *data)
{
   int rand_num = 0;
   int i = 0;
   int x, y, w, h;

   printf("aa\n");
   timer_loop++;

   for (i = 0; i <= num; i++)
     {
        rand_num = rand() % 11;
        printf("%d\n", rand_num);
        if (rand_num >= 4)
          {
             elm_grid_pack_get(btn[i], &x, &y, &w, &h);
             x += (100 / num_loop) / 1.1;
             printf("%d %d\n", x, num_loop);
             elm_grid_pack_set(btn[i], x, y, w, h);
          }
     }
   if (timer_loop >= num_loop)
      return ECORE_CALLBACK_CANCEL;
   return ECORE_CALLBACK_RENEW;
}

void
create_cars(void)
{
   char car_num[100] = {0};
   Evas_Object *grid = elm_grid_add(box);

   evas_object_size_hint_weight_set(grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, grid);
   evas_object_show(grid);

   btn_pos[num] = 0;
   sprintf(car_num, "Car # %d", num + 1);

   btn[num] = elm_image_add(box);
   elm_image_file_set(btn[num], "car.jpg", NULL);
   elm_grid_pack(grid, btn[num], 0, 0, 10, 50);
   elm_object_text_set(btn[num], car_num);
   evas_object_show(btn[num]);
}

void
_start_cb(void *a, Evas_Object *obj, void *event_info)
{
   int num_cars = atoi(elm_entry_entry_get(en1));
   int i = 0;

   for (i = 0; i < num_cars; i++)
     {
        num = i;
        create_cars();
     }
   num_loop = atoi(elm_entry_entry_get(en2));
   timer_loop = 0;
   timer = ecore_timer_add(1.0, _timer_cb, NULL);
}

void
_exit_cb(void *a, Evas_Object *obj, void *event_info)
{
   elm_exit();
}

EAPI_MAIN int
elm_main(int argc, char **argv)
{
   Evas_Object *win = NULL;
   srand(time(NULL));

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   win = elm_win_util_standard_add("main", "Main");
   elm_win_autodel_set(win, EINA_TRUE);
   evas_object_resize(win, 1024, 800);
   evas_object_show(win);

   Evas_Object *btn1, *btn2, *label;
   box = elm_box_add(win);
   evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, box);
   evas_object_show(box);

   label = elm_label_add(win);
   evas_object_size_hint_weight_set(label, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(label, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, label);
   elm_object_text_set(label, "<b>Racing Game!</b>");
   evas_object_show(label);

   en1 = elm_entry_add(box);
   evas_object_size_hint_weight_set(en1, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en1, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, en1);
   evas_object_show(en1);

   en2 = elm_entry_add(box);
   evas_object_size_hint_weight_set(en2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(en2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, en2);
   evas_object_show(en2);

   btn1 = elm_button_add(box);
   evas_object_size_hint_weight_set(btn1, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(btn1, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, btn1);
   elm_object_text_set(btn1, "Start!");
   evas_object_smart_callback_add(btn1, "clicked", _start_cb, NULL);
   evas_object_show(btn1);

   btn2 = elm_button_add(box);
   evas_object_size_hint_weight_set(btn2, EVAS_HINT_EXPAND, 0.0);
   evas_object_size_hint_align_set(btn2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, btn2);
   elm_object_text_set(btn2, "Exit");
   evas_object_smart_callback_add(btn2, "clicked", _exit_cb, NULL);
   evas_object_show(btn2);

   elm_run();

   return 0;
}
ELM_MAIN()
