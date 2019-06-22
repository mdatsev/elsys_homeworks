json.extract! thread_obj, :id, :thread_id, :value, :created_at, :updated_at
json.url thread_obj_url(thread_obj, format: :json)
