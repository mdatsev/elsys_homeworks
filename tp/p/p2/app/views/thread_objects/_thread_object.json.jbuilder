json.extract! thread_object, :id, :thread_id, :value, :created_at, :updated_at
json.url thread_object_url(thread_object, format: :json)
